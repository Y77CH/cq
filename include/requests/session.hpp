#ifndef REQUESTS_SESSION_HPP
#define REQUESTS_SESSION_HPP

#include <string>
#include <string_view>

#include "requests/options.hpp"
#include "requests/request.hpp"
#include "requests/response.hpp"


namespace Requests {

/**
 * @brief Single connection session
 *
 * @note:
 *  Session ignores Host header.
 *  If you want to connect to other host,
 *  you must create another session.
 */
class Session
{
public:
    // Stores scheme, host and port
    Url base_url;

    // Added to each request
    Headers common_headers;


    // Prepare and send a request
    Response send(Request r);


    template<typename ...Args>
    Response delet(Url target_url, const Args & ...args);

    template<typename ...Args>
    Response get(Url target_url, const Args & ...args);

    template<typename ...Args>
    Response head(Url target_url, const Args & ...args);

    template<typename ...Args>
    Response options(Url target_url, const Args & ...args);

    template<typename ...Args>
    Response patch(Url target_url, const Args & ...args);

    template<typename ...Args>
    Response post(Url target_url, const Args & ...args);

    template<typename ...Args>
    Response put(Url target_url, const Args & ...args);
};

} // namespace Requests

#include "requests/session.ipp"

#endif // REQUESTS_SESSION_HPP