#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

// Receive messages from server
void receive_messages(tcp::socket& socket) {
    try {
        char data[1024];
        while (true) {
            size_t length = socket.read_some(boost::asio::buffer(data));
            std::cout << "\nALERT RECEIVED: " << std::string(data, length) << std::endl;
        }
    } catch (...) {
        std::cout << "Disconnected from server\n";
    }
}

int main() {
    boost::asio::io_context io_context;
    tcp::socket socket(io_context);

    socket.connect(tcp::endpoint(boost::asio::ip::make_address("127.0.0.1"), 12345));

    std::string username;
    std::cout << "Enter your username: ";
    std::getline(std::cin, username);

    std::vector<std::string> circle;

    std::cout << "Connected to server\n";

    std::thread(receive_messages, std::ref(socket)).detach();

    while (true) {
        std::string input;
        std::getline(std::cin, input);

        if (input == "alert") {
            std::string msg = "{ \"type\": \"alert\", \"user\": \"" + username + "\", \"message\": \"HELP\" }";
            boost::asio::write(socket, boost::asio::buffer(msg));
        }

        else if (input.rfind("add ", 0) == 0) {
            std::string user = input.substr(4);
            circle.push_back(user);
            std::cout << user << " added to your circle\n";
        }

        else if (input.rfind("remove ", 0) == 0) {
            std::string user = input.substr(7);
            circle.erase(std::remove(circle.begin(), circle.end(), user), circle.end());
            std::cout << user << " removed from your circle\n";
        }

        else if (input == "list") {
            std::cout << "Your circle:\n";
            for (auto& u : circle) {
                std::cout << "- " << u << std::endl;
            }
        }

        else {
            std::string msg = "{ \"type\": \"status\", \"user\": \"" + username + "\", \"message\": \"" + input + "\" }";
            boost::asio::write(socket, boost::asio::buffer(msg));
        }
    }

    return 0;
}
