#include <iostream>
#include <thread>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

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

    std::cout << "Connected to server\n";

    std::thread(receive_messages, std::ref(socket)).detach();

    while (true) {
        std::string input;
        std::getline(std::cin, input);

        if (input == "alert") {
            std::string msg = "{ \"type\": \"alert\", \"message\": \"HELP\" }";
            boost::asio::write(socket, boost::asio::buffer(msg));
        }
    }

    return 0;
}
