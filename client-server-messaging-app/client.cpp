#include <boost/asio.hpp>
#include <iostream>
#include <thread>

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
        std::cout << "Server: " << data << std::endl;
    }
}

void chat_client(const std::string &server_ip)
{
    try
    {
        boost::asio::io_context io_context;
        tcp::socket socket(io_context);
        socket.connect(tcp::endpoint(boost::asio::ip::make_address(server_ip), 12345));

        // Start reader thread
        std::thread reader_thread(read_messages, std::ref(socket));

        // Main thread handles writing
        while (true)
        {
            std::string message;
            std::cout << "You: ";
            std::getline(std::cin, message);
            boost::asio::write(socket, boost::asio::buffer(message));
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
    std::string server_ip;
    std::cout << "Enter server IP: ";
    std::cin >> server_ip;
    std::cin.ignore(); // Ignore leftover newline from std::cin
    chat_client(server_ip);
    return 0;
}