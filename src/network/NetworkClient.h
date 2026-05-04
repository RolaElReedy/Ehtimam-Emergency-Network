#pragma once
#include <boost/asio.hpp>
#include <string>
#include <functional>
#include <thread>
using boost::asio::ip::tcp;
class NetworkClient {
public:
    NetworkClient();
    ~NetworkClient();
    bool connectToServer(const std::string& host, int port);
    void sendMessage(const std::string& message);
    void disconnect();
    bool isConnected() const { return connected_; }
    std::function<void(const std::string&)> onMessageReceived;
    std::function<void()> onDisconnected;
private:
    void startRead();
    boost::asio::io_context io_context_;
    tcp::socket socket_;
    boost::asio::streambuf buffer_;
    std::thread io_thread_;
    bool connected_ = false;
};
