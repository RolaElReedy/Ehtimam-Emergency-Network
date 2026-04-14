#include <iostream>
#include <vector>
#include <memory>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::vector<std::shared_ptr<tcp::socket>> clients;

void handle_client(std::shared_ptr<tcp::socket> socket) {
    try {
        char data[1024];
        while (true) {
            size_t length = socket->read_some(boost::asio::buffer(data));
            std::string message(data, length);

            std::cout << "Received: " << message << std::endl;

            // Broadcast to all clients
            for (auto& client : clients) {
                if (client != socket) {
                    boost::asio::write(*client, boost::asio::buffer(message));
                }
            }
        }
    } catch (...) {
        std::cout << "Client disconnected\n";
    }
}

int main() {
    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12345));

    std::cout << "Server started on port 12345\n";

    while (true) {
        auto socket = std::make_shared<tcp::socket>(io_context);
        acceptor.accept(*socket);
        clients.push_back(socket);

        std::thread(handle_client, socket).detach();
    }

    return 0;
}
