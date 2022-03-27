#include "server.h"
using namespace http;

Server::Server(std::string_view address, std::string_view port) 
    : acceptor_(io_context_)
{
    boost::asio::ip::tcp::resolver resolver(io_context_);
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(address, port).begin();
    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen();

    message_ =
    "HTTP/1.0 200 OK\r\n"
    "Content-Length: 55\r\n"
    "\r\n"
    "<html>\r\n"
    "   <body>\r\n"
    "       <i>Hello world</i>\r\n"
    "   </body>\r\n"
    "</html>";

    do_accept();
}

void Server::run() {
    io_context_.run();
}

void Server::do_accept() {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
            if (!ec) {
                do_write(std::move(socket));
            }

            do_accept();
        });
}

void Server::do_write(boost::asio::ip::tcp::socket socket) {
    boost::asio::async_write(socket, boost::asio::buffer(message_),
        [](boost::system::error_code, std::size_t) {

        }); 
}