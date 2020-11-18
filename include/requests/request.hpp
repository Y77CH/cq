#ifndef REQUESTS_REQUEST_HPP
#define REQUESTS_REQUEST_HPP

#include <string>
#include <vector>

#include "requests/options.hpp"


namespace Requests {

class Request
{
public:
    Method      method;
    std::string target;
    uint16_t    version;
    Headers     headers;
    Body        body;


    /* Helper setters */
    void set(const Body    &b)  noexcept { body = b; }
    void set(const Headers &hs) noexcept { headers = hs; }
};

} // namespace Requests

#endif // REQUESTS_REQUEST_HPP