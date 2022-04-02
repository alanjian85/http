#include "request_parser.h"
using namespace http;

RequestParser::RequestParser() {
    state_ = State::kMethodStart;
}

RequestParser::Result consume(Request& req, char c) {

}

bool RequestParser::isChar(char c) {
    return c >= 0 && c <= 127;
}

bool RequestParser::isCtl(char c) {
    return (c >= 0 && c <= 31) || c == 127;
}

bool RequestParser::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool RequestParser::isSeparator(char c) {
    switch (c) {
        case '(': case ')': case '<': case '>': case '@':
        case ',': case ';': case ':': case '\\': case '"':
        case '/': case '[': case ']': case '?': case '=':
        case '{': case '}': case ' ': case '\t':
            return true;
    }
    return false;
}