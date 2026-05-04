#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <nlohmann/json.hpp>
#include "../src/logic/AlertManager.h"
#include "../src/logic/CircleManager.h"
using json = nlohmann::json;

TEST(MessageTest, AlertMessageFormat) {
    json j; j["type"] = "alert"; j["user"] = "rola"; j["message"] = "HELP";
    EXPECT_EQ(j["type"], "alert");
    EXPECT_EQ(j["user"], "rola");
}
TEST(MessageTest, StatusMessageFormat) {
    json j; j["type"] = "status"; j["user"] = "omar"; j["message"] = "I am safe";
    EXPECT_EQ(j["type"], "status");
    EXPECT_FALSE(j["message"].get<std::string>().empty());
}
TEST(MessageTest, SuggestMessageFormat) {
    json j; j["type"] = "suggest"; j["user"] = "christine"; j["message"] = "fire";
    EXPECT_EQ(j["type"], "suggest");
}
TEST(MessageTest, ParseValidJson) {
    std::string raw = "{\"type\":\"alert\",\"user\":\"rola\",\"message\":\"HELP\"}";
    EXPECT_NO_THROW({ auto j = json::parse(raw); EXPECT_EQ(j["type"], "alert"); });
}
TEST(MessageTest, ParseInvalidJson) {
    std::string raw = "not valid json{{";
    EXPECT_THROW(json::parse(raw), json::parse_error);
}
TEST(MessageTest, MissingKeyDefaultValue) {
    json j; j["type"] = "status";
    EXPECT_EQ(j.value("user", "unknown"), "unknown");
}
TEST(MessageTest, SerializationRoundtrip) {
    json original; original["type"] = "alert"; original["user"] = "rola"; original["message"] = "HELP";
    EXPECT_EQ(original, json::parse(original.dump()));
}
TEST(AlertManagerTest, InitialStateIsNormal) {
    AlertManager am;
    EXPECT_EQ(am.getState(), AlertState::Normal);
}
TEST(AlertManagerTest, TriggerSetsActiveState) {
    AlertManager am;
    am.triggerAlert("rola");
    EXPECT_EQ(am.getState(), AlertState::Active);
}
TEST(AlertManagerTest, ResolveResetsState) {
    AlertManager am;
    am.triggerAlert("rola");
    am.resolveAlert("rola");
    EXPECT_EQ(am.getState(), AlertState::Normal);
}
TEST(AlertManagerTest, AcknowledgmentTracked) {
    AlertManager am;
    am.triggerAlert("rola");
    am.addAcknowledgment("omar");
    am.addAcknowledgment("christine");
    EXPECT_EQ(am.getAcknowledgments().size(), 2u);
}
TEST(CircleManagerTest, AddMember) {
    CircleManager cm;
    cm.addMember("omar");
    EXPECT_TRUE(cm.isMember("omar"));
}
TEST(CircleManagerTest, RemoveMember) {
    CircleManager cm;
    cm.addMember("omar");
    cm.removeMember("omar");
    EXPECT_FALSE(cm.isMember("omar"));
}
TEST(CircleManagerTest, OnlineStatus) {
    CircleManager cm;
    cm.addMember("omar");
    cm.setOnline("omar", true);
    EXPECT_TRUE(cm.getStatuses().at("omar"));
}
TEST(CircleManagerTest, NoDuplicates) {
    CircleManager cm;
    cm.addMember("omar");
    cm.addMember("omar");
    EXPECT_EQ(cm.getMembers().size(), 1u);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
