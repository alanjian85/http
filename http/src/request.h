#ifndef HTTP_REQUEST_H_
#define HTTP_REQUEST_H_

#include <map>
#include <string>

namespace http {
    struct Request {
        std::string method;
        std::string uri;
        int version_major;
        int version_minor;
        std::map<std::string, std::string> headers;
    };
}

#endif // HTTP_REQUEST_H_