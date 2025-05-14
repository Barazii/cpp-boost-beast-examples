
#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <cstdlib>

using boost::asio::ip::tcp;

void read_messages(tcp::socket &socket)
{
    char data[1024];
    while (true)
    {
        std::memset(data, 0, sizeof(data));
        boost::system::error_code error;
        socket.read_some(boost::asio::buffer(data), error);
        if (error)
            break;
        std::cout << "Client: " << data << std::endl;
    }
}

void handle_client(tcp::socket &&socket)
{
    try
    {
        std::thread reader_thread(read_messages, std::ref(socket));

        while (true)
        {
            // Send response
            std::string response;
            std::cout << "You: ";
            std::getline(std::cin, response);
            boost::asio::write(socket, boost::asio::buffer(response));
        }
        reader_thread.join();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

int main()
{
    try
    {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12345));
        tcp::socket socket(io_context);
        std::cout << "Server started. Waiting for client..." << std::endl;
        acceptor.accept(socket);
        std::cout << "Client connected!" << std::endl;
        handle_client(std::move(socket));
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}