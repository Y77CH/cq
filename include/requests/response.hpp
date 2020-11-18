#ifndef REQUESTS_RESPONSE_HPP
#define REQUESTS_RESPONSE_HPP

#include <string>

#include "requests/options/body.hpp"
#include "requests/options/headers.hpp"


namespace Requests {

struct Response
{
    Body        body;
    Headers     headers;
    std::string reason;
    uint16_t    status_code = 0;
};

} // namespace Requests

#endif // REQUESTS_RESPONSE_HPP