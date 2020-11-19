#ifndef REQUESTS_RESPONSE_HPP
#define REQUESTS_RESPONSE_HPP

#include <string>

#include "requests/options/headers.hpp"


namespace Requests {

struct Response
{
    Headers     headers;
    std::string reason;
    uint16_t    status_code = 0;
    std::string text;
};

} // namespace Requests

#endif // REQUESTS_RESPONSE_HPP