#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include <boost/asio.hpp>

#include "server.h"
using namespace http;

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: http <address> <port>\n";
        return EXIT_FAILURE;
    }

    Server server(argv[1], argv[2]);
    server.run();

    return EXIT_SUCCESS;
}