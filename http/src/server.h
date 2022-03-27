#ifndef HTTP_SERVER_H_
#define HTTP_SERVER_H_

#include <string>
#include <string_view>

#include <boost/asio.hpp>

namespace http {
    class Server {
    public:
        Server(std::string_view address, std::string_view port);

        void run();
    private:
        void do_accept();
        void do_write(boost::asio::ip::tcp::socket socket);

        boost::asio::io_context io_context_;
        boost::asio::ip::tcp::acceptor acceptor_;

        std::string message_;
    };
}

#endif // HTTP_SERVER_H_