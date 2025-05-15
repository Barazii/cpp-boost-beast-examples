#include <cstdlib>
#include <boost/asio.hpp>
#include <iostream>
#include <thread>

using boost::asio::ip::tcp;

void read_msg(tcp::socket &socket)
{
    std::string data(1024, '\0');
    while (true)
    {
        if (socket.read_some(boost::asio::buffer(data, data.max_size())))
        {
            std::cout << "Client: " << data << std::endl;
            data.clear();
            data.resize(1024);
        }
    }
}

void write_msg(tcp::socket &socket)
{
    std::string response;
    while (true)
    {
        response.clear();
        std::cout << "You: ";
        std::getline(std::cin, response);
        socket.write_some(boost::asio::buffer(response, response.max_size()));
    }
}

void communicate(tcp::socket &&socket)
{
    std::thread read_thread{read_msg, std::ref(socket)};
    std::thread write_thread{write_msg, std::ref(socket)};

    read_thread.join();
    write_thread.join();
}

int main()
{
    boost::asio::io_context ioc{};
    tcp::acceptor acceptor{ioc, tcp::endpoint(tcp::v4(), 12345)};
    tcp::socket socket{ioc};
    acceptor.accept(socket);
    std::cout << "Client connected." << std::endl;
    communicate(std::move(socket));

    return EXIT_SUCCESS;
}