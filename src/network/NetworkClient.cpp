#include "NetworkClient.h"
#include <iostream>
NetworkClient::NetworkClient() : socket_(io_context_) {}
NetworkClient::~NetworkClient() { disconnect(); }
bool NetworkClient::connectToServer(const std::string& host, int port) {
    try {
        tcp::resolver resolver(io_context_);
        auto endpoints = resolver.resolve(host, std::to_string(port));
        boost::asio::connect(socket_, endpoints);
        connected_ = true;
        startRead();
        io_thread_ = std::thread([this]() { io_context_.run(); });
        return true;
    } catch (...) { return false; }
}
void NetworkClient::sendMessage(const std::string& message) {
    if (!connected_) return;
    try {
        boost::asio::write(socket_, boost::asio::buffer(message + "\n"));
    } catch (...) { connected_ = false; }
}
void NetworkClient::disconnect() {
    connected_ = false;
    io_context_.stop();
    if (io_thread_.joinable()) io_thread_.join();
    try { socket_.close(); } catch (...) {}
}
void NetworkClient::startRead() {
    boost::asio::async_read_until(socket_, buffer_, "\n",
        [this](boost::system::error_code ec, std::size_t) {
            if (!ec) {
                std::istream is(&buffer_);
                std::string line;
                std::getline(is, line);
                if (onMessageReceived) onMessageReceived(line);
                startRead();
            } else {
                connected_ = false;
                if (onDisconnected) onDisconnected();
            }
        });
}
