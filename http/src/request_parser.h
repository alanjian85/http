#ifndef HTTP_REQUEST_PARSER_H_
#define HTTP_REQUEST_PARSER_H_

#include <utility>

#include "request.h"

namespace http {
    class RequestParser {
    public:
        enum class Result {
            kGood,
            kBad,
            kUnknown
        };

        template <typename Iterator>
        std::pair<Result, Iterator> parse(Request& req, Iterator begin, Iterator end) {
            while (begin != end) {
                auto result = consume(req, *begin++);
                if (result == Result::kGood || result == Result::kBad)
                    return std::make_pair(result, begin);
            }
            return std::make_pair(Result::kUnknown, begin);
        }
    private:
        enum class State {
            kMethodStart,
            kMethod,
            kURI,
            kVersionH,
            kVersionT,
            kVersionT,
            kVersionP,
            kVersionSlash,
            kVersionMajorStart,
            kVersionMajor,
            kVersionMinorStart,
            kVersionMinor,
            kNewline1,
            kHeaderStart,
            kHeaderName,
            kHeaderSpace,
            kHeaderValue,
            kNewline2,
            kNewline3
        };

        Result consume(Request& req, char c);

        State state_;
    };
}

#endif // HTTP_REQUEST_PARSER_H_