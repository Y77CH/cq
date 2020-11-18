#ifndef REQUESTS_IMPL_API_IPP
#define REQUESTS_IMPL_API_IPP

#include "requests/options/url.hpp"
#include "requests/response.hpp"
#include "requests/session.hpp"


namespace Requests {

template<typename ...Args>
Response delet(const Url &url, const Args & ...args)
{
    Session s {
        .scheme = url.scheme,
        .host = url.host,
        .port = url.port
    };

    std::string target = url.path +
        (url.query.empty() ? "" : "?") + url.query +
        (url.fragment.empty() ? "" : "#") + url.fragment;

    return s.delet(target, args...);
}


template<typename ...Args>
Response get(const Url &url, const Args & ...args)
{
    Session s {
        .scheme = url.scheme,
        .host = url.host,
        .port = url.port
    };

    std::string target = url.path +
        (url.query.empty() ? "" : "?") + url.query +
        (url.fragment.empty() ? "" : "#") + url.fragment;

    return s.get(target, args...);
}


template<typename ...Args>
Response head(const Url &url, const Args & ...args)
{
    Session s {
        .scheme = url.scheme,
        .host = url.host,
        .port = url.port
    };

    std::string target = url.path +
        (url.query.empty() ? "" : "?") + url.query +
        (url.fragment.empty() ? "" : "#") + url.fragment;

    return s.head(target, args...);
}


template<typename ...Args>
Response options(const Url &url, const Args & ...args)
{
    Session s {
        .scheme = url.scheme,
        .host = url.host,
        .port = url.port
    };

    std::string target = url.path +
        (url.query.empty() ? "" : "?") + url.query +
        (url.fragment.empty() ? "" : "#") + url.fragment;

    return s.options(target, args...);
}


template<typename ...Args>
Response patch(const Url &url, const Args & ...args)
{
    Session s {
        .scheme = url.scheme,
        .host = url.host,
        .port = url.port
    };

    std::string target = url.path +
        (url.query.empty() ? "" : "?") + url.query +
        (url.fragment.empty() ? "" : "#") + url.fragment;

    return s.patch(target, args...);
}


template<typename ...Args>
Response post(const Url &url, const Args & ...args)
{
    Session s {
        .scheme = url.scheme,
        .host = url.host,
        .port = url.port
    };

    std::string target = url.path +
        (url.query.empty() ? "" : "?") + url.query +
        (url.fragment.empty() ? "" : "#") + url.fragment;

    return s.post(target, args...);
}


template<typename ...Args>
Response put(const Url &url, const Args & ...args)
{
    Session s {
        .scheme = url.scheme,
        .host = url.host,
        .port = url.port
    };

    std::string target = url.path +
        (url.query.empty() ? "" : "?") + url.query +
        (url.fragment.empty() ? "" : "#") + url.fragment;

    return s.put(target, args...);
}

} // namespace Requests

#endif // REQUESTS_IMPL_API_IPP