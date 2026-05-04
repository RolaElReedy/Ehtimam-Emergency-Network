#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <string>
#include <fstream>
#include <sstream>
#include <mutex>
#include <boost/asio.hpp>
#include <sqlite3.h>
#include <nlohmann/json.hpp>
using boost::asio::ip::tcp;
using json = nlohmann::json;
std::vector<std::shared_ptr<tcp::socket>> clients;
std::mutex clients_mutex;
sqlite3* db;
void init_db() {
    sqlite3_open("ehtimam.db", &db);
    const char* sql = "CREATE TABLE IF NOT EXISTS messages (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, type TEXT, message TEXT, timestamp DATETIME DEFAULT CURRENT_TIMESTAMP);";
    sqlite3_exec(db, sql, nullptr, nullptr, nullptr);
    std::cout << "[DB] Database initialized.\n";
}
void log_message(const std::string& username, const std::string& type, const std::string& message) {
    std::string sql = "INSERT INTO messages (username, type, message) VALUES ('" + username + "', '" + type + "', '" + message + "');";
    sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
}
std::string call_llm(const std::string& situation) {
    const char* api_key = getenv("ANTHROPIC_API_KEY");
    if (!api_key) return "[LLM] Set ANTHROPIC_API_KEY to enable AI suggestions.";
    json body;
    body["model"] = "claude-sonnet-4-20250514";
    body["max_tokens"] = 300;
    body["messages"] = json::array({{{"role","user"},{"content","You are an emergency response assistant. Give concise, calm advice for: " + situation}}});
    std::ofstream req("/tmp/llm_req.json");
    req << body.dump(); req.close();
    std::string cmd = std::string("curl -s https://api.anthropic.com/v1/messages ")
        + "-H 'Content-Type: application/json' "
        + "-H 'x-api-key: " + api_key + "' "
        + "-H 'anthropic-version: 2023-06-01' "
        + "-d @/tmp/llm_req.json > /tmp/llm_resp.json 2>/dev/null";
    system(cmd.c_str());
    std::ifstream resp("/tmp/llm_resp.json");
    std::stringstream ss; ss << resp.rdbuf();
    try {
        auto j = json::parse(ss.str());
        return "[AI Advice]: " + j["content"][0]["text"].get<std::string>();
    } catch (...) { return "[LLM] Could not parse response."; }
}
void broadcast(const std::string& msg, std::shared_ptr<tcp::socket> sender) {
    std::lock_guard<std::mutex> lock(clients_mutex);
    for (auto& client : clients)
        if (client != sender)
            try { boost::asio::write(*client, boost::asio::buffer(msg + "\n")); } catch (...) {}
}
void handle_client(std::shared_ptr<tcp::socket> socket) {
    boost::asio::streambuf buf;
    try {
        while (true) {
            boost::asio::read_until(*socket, buf, "\n");
            std::istream is(&buf);
            std::string raw; std::getline(is, raw);
            if (raw.empty()) continue;
            std::cout << "Received: " << raw << std::endl;
            try {
                auto j = json::parse(raw);
                std::string type = j.value("type","status");
                std::string user = j.value("user","unknown");
                std::string msg  = j.value("message","");
                log_message(user, type, msg);
                if (type == "suggest") {
                    std::string advice = call_llm(msg);
                    boost::asio::write(*socket, boost::asio::buffer(advice + "\n"));
                    continue;
                }
            } catch (...) {}
            broadcast(raw, socket);
        }
    } catch (...) { std::cout << "Client disconnected\n"; }
    std::lock_guard<std::mutex> lock(clients_mutex);
    clients.erase(std::remove(clients.begin(), clients.end(), socket), clients.end());
}
int main() {
    init_db();
    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12345));
    std::cout << "Server started on port 12345\n";
    while (true) {
        auto socket = std::make_shared<tcp::socket>(io_context);
        acceptor.accept(*socket);
        { std::lock_guard<std::mutex> lock(clients_mutex); clients.push_back(socket); }
        std::cout << "New client connected.\n";
        std::thread(handle_client, socket).detach();
    }
    sqlite3_close(db);
    return 0;
}
