#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// Test 1: JSON alert message is well-formed
TEST(MessageTest, AlertMessageFormat) {
    json j;
    j["type"] = "alert";
    j["user"] = "rola";
    j["message"] = "HELP";
    EXPECT_EQ(j["type"], "alert");
    EXPECT_EQ(j["user"], "rola");
    EXPECT_EQ(j["message"], "HELP");
}

// Test 2: JSON status message is well-formed
TEST(MessageTest, StatusMessageFormat) {
    json j;
    j["type"] = "status";
    j["user"] = "omar";
    j["message"] = "I am safe";
    EXPECT_EQ(j["type"], "status");
    EXPECT_FALSE(j["message"].get<std::string>().empty());
}

// Test 3: JSON suggest message is well-formed
TEST(MessageTest, SuggestMessageFormat) {
    json j;
    j["type"] = "suggest";
    j["user"] = "christine";
    j["message"] = "there is a fire";
    EXPECT_EQ(j["type"], "suggest");
}

// Test 4: Parsing valid JSON succeeds
TEST(MessageTest, ParseValidJson) {
    std::string raw = "{\"type\":\"alert\",\"user\":\"rola\",\"message\":\"HELP\"}";
    EXPECT_NO_THROW({
        auto j = json::parse(raw);
        EXPECT_EQ(j["type"], "alert");
    });
}

// Test 5: Parsing invalid JSON throws
TEST(MessageTest, ParseInvalidJson) {
    std::string raw = "not valid json{{";
    EXPECT_THROW(json::parse(raw), json::parse_error);
}

// Test 6: json::value with default on missing key
TEST(MessageTest, MissingKeyDefaultValue) {
    json j;
    j["type"] = "status";
    std::string user = j.value("user", "unknown");
    EXPECT_EQ(user, "unknown");
}

// Test 7: Empty message field is detectable
TEST(MessageTest, EmptyMessageDetectable) {
    json j;
    j["type"] = "status";
    j["user"] = "rola";
    j["message"] = "";
    EXPECT_TRUE(j["message"].get<std::string>().empty());
}

// Test 8: Alert type is distinguishable from status
TEST(MessageTest, AlertVsStatus) {
    json alert, status;
    alert["type"] = "alert";
    status["type"] = "status";
    EXPECT_NE(alert["type"], status["type"]);
}

// Test 9: JSON serialization roundtrip
TEST(MessageTest, SerializationRoundtrip) {
    json original;
    original["type"] = "alert";
    original["user"] = "rola";
    original["message"] = "HELP";
    std::string serialized = original.dump();
    json parsed = json::parse(serialized);
    EXPECT_EQ(original, parsed);
}

// Test 10: suggest type is distinguishable
TEST(MessageTest, SuggestTypeCheck) {
    json j;
    j["type"] = "suggest";
    j["message"] = "fire in building";
    EXPECT_EQ(j.value("type",""), "suggest");
    EXPECT_FALSE(j["message"].get<std::string>().empty());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
