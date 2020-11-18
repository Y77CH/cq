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
    Url::Scheme scheme;
    std::string host;
    uint16_t    port;

    // Added to each request
    Headers common_headers;


    // Send prepared request
    Response send(const Request &r);


    template<typename ...Args>
    Response delet(std::string_view target, const Args & ...args);


    template<typename ...Args>
    Response get(std::string_view target, const Args & ...args);


    template<typename ...Args>
    Response head(std::string_view target, const Args & ...args);


    template<typename ...Args>
    Response options(std::string_view target, const Args & ...args);


    template<typename ...Args>
    Response patch(std::string_view target, const Args & ...args);


    template<typename ...Args>
    Response post(std::string_view target, const Args & ...args);


    template<typename ...Args>
    Response put(std::string_view target, const Args & ...args);

private:
    void prepare_request(Request &r) const noexcept
    {
        r.version = 11;
        r.headers["host"] = this->host + ":" + std::to_string(this->port);
        r.headers.insert(common_headers.begin(), common_headers.end());
    }

    template<typename T, typename ...Args>
    void prepare_request(Request &r, const T &t, const Args & ...args) const noexcept;
};

} // namespace Requests

#include "requests/impl/session.ipp"

#endif // REQUESTS_SESSION_HPP