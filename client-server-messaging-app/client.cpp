#include <boost/asio.hpp>
#include <iostream>
#include <thread>

using boost::asio::ip::tcp;

void read_messages(tcp::socket &socket)
{
    std::string data(1024, '\0');
    while (true)
    {
        if (socket.read_some(boost::asio::buffer(data, data.max_size())))
        {
            std::cout << "Server: " << data << std::endl;
            data.clear();
            data.resize(1024);
        }
    }
}

void write_messages(tcp::socket &socket)
{
    std::string message;
    while (true)
    {
        message.clear();
        std::cout << "You: ";
        std::getline(std::cin, message);
        boost::asio::write(socket, boost::asio::buffer(message, message.max_size()));
    }
}

void communicate(tcp::socket && socket)
{
    std::thread reader_thread{read_messages, std::ref(socket)};
    std::thread writer_thread{write_messages, std::ref(socket)};

    reader_thread.join();
    writer_thread.join();
}

int main()
{
    std::string server_ip;
    std::cout << "Enter server IP: ";
    std::cin >> server_ip;
    std::cin.ignore(); // Ignore leftover newline from std::cin

    boost::asio::io_context io_context;
    tcp::socket socket(io_context);
    socket.connect(tcp::endpoint(boost::asio::ip::make_address(server_ip), 12345));

    communicate(std::move(socket));
}