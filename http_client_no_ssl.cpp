#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <string>
#include <iostream>

const std::string hostname{"www.example.com"};
constexpr int port = 80;
const std::string target = "/";
constexpr int version = 11;

namespace http = boost::beast::http;
using tcp = boost::asio::ip::tcp;

int main(int argc, char **argv)
{
    boost::asio::io_context io_context{};
    tcp::resolver resolver{io_context};
    boost::beast::tcp_stream tcp_stream{io_context};

    auto const endpoint_entries = resolver.resolve(hostname, std::to_string(port));
    tcp_stream.connect(endpoint_entries);

    http::request<http::string_body> request{http::verb::get, target, version};
    request.set(http::field::host, hostname);

    http::write(tcp_stream, request);

    boost::beast::flat_buffer buffer;
    http::response<http::dynamic_body> response;

    http::read(tcp_stream, buffer, response);

    std::cout << response << std::endl;

    tcp_stream.socket().shutdown(tcp::socket::shutdown_both);

    return EXIT_SUCCESS;
}