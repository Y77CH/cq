#ifndef REQUESTS_RESPONSE_HPP
#define REQUESTS_RESPONSE_HPP

#include <list>
#include <string>

#include "requests/request.hpp"


namespace Requests {

struct Response
{
    std::string         encoding;
    Headers             headers;
    std::list<Response> history;
    std::string         reason;
    Request             request;
    uint16_t            status_code = 0;
    std::string         text;
    Url                 url;


    [[deprecated("Not implemented!")]]
    Json json() const noexcept { return Json{""}; }
};

} // namespace Requests

#endif // REQUESTS_RESPONSE_HPP