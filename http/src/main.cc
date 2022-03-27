#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include <boost/asio.hpp>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: http <address> <port>\n";
        return EXIT_FAILURE;
    }

    boost::asio::io_context io_context;

    boost::asio::ip::tcp::resolver resolver(io_context);
    auto address = argv[1];
    auto port = argv[2];
    auto endpoint = static_cast<boost::asio::ip::tcp::endpoint>(*resolver.resolve(address, port).begin());

    boost::asio::ip::tcp::acceptor acceptor(io_context);
    acceptor.open(endpoint.protocol());
    acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor.bind(endpoint);
    acceptor.listen();

    for (;;) {
        boost::asio::ip::tcp::socket socket(io_context);
        acceptor.accept(socket);

        const char message[] = 
        "HTTP/1.0 200 OK\r\n"
        "Content-Length: 55\r\n"
        "\r\n"
        "<html>\r\n"
        "   <body>\r\n"
        "       <i>Hello world</i>\r\n"
        "   </body>\r\n"
        "</html>";

        boost::system::error_code ignored_error;
        boost::asio::write(socket, boost::asio::buffer(message, sizeof(message)), ignored_error);
    }

    return EXIT_SUCCESS;
}