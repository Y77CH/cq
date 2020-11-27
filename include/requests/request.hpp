#ifndef REQUESTS_REQUEST_HPP
#define REQUESTS_REQUEST_HPP

#include <string>

#include "requests/options.hpp"


namespace Requests {

struct Request
{
    Method      method;
    Url         target;
    std::string version; // HTTP/1.1
    Headers     headers;
    std::string body;


    /* Helper setters */
    template<typename T, typename ...Ts>
    void set(const T &t, const Ts & ...ts) noexcept { set(t); set(ts...); }

    void set() noexcept {}

    void set(const Auth     &) noexcept;
    void set(const Data     &) noexcept;
    void set(const Fragment &) noexcept;
    void set(const Header   &) noexcept;
    void set(const Headers  &) noexcept;
    void set(const Json     &) noexcept;
    void set(const Query    &) noexcept;
    void set(const Text     &) noexcept;
};

} // namespace Requests

#endif // REQUESTS_REQUEST_HPP