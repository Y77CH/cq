#ifndef REQUESTS_SESSION_IPP
#define REQUESTS_SESSION_IPP

#include "requests/session.hpp"


namespace Requests {

template<typename ...Args>
Response Session::delet(const Url target_url, const Args & ...args)
{
    Request r {
        .method = Method::DELETE,
        .target = target_url,
        .headers = {
            {"User-Agent", "C++ Requests"}
        }
    };

    r.set(args...);

    return send(r);
}


template<typename ...Args>
Response Session::get(const Url target_url, const Args & ...args)
{
    Request r {
        .method = Method::GET,
        .target = target_url,
        .headers = {
            {"User-Agent", "C++ Requests"}
        }
    };

    r.set(args...);

    return send(r);
}


template<typename ...Args>
Response Session::head(const Url target_url, const Args & ...args)
{
    Request r {
        .method = Method::HEAD,
        .target = target_url,
        .headers = {
            {"User-Agent", "C++ Requests"}
        }
    };

    r.set(args...);

    return send(r);
}


template<typename ...Args>
Response Session::options(const Url target_url, const Args & ...args)
{
    Request r {
        .method = Method::OPTIONS,
        .target = target_url,
        .headers = {
            {"User-Agent", "C++ Requests"}
        }
    };

    r.set(args...);

    return send(r);
}


template<typename ...Args>
Response Session::patch(const Url target_url, const Args & ...args)
{
    Request r {
        .method = Method::PATCH,
        .target = target_url,
        .headers = {
            {"User-Agent", "C++ Requests"}
        }
    };

    r.set(args...);

    return send(r);
}


template<typename ...Args>
Response Session::post(const Url target_url, const Args & ...args)
{
    Request r {
        .method = Method::POST,
        .target = target_url,
        .headers = {
            {"User-Agent", "C++ Requests"}
        }
    };

    r.set(args...);

    return send(r);
}


template<typename ...Args>
Response Session::put(const Url target_url, const Args & ...args)
{
    Request r {
        .method = Method::PUT,
        .target = target_url,
        .headers = {
            {"User-Agent", "C++ Requests"}
        }
    };

    r.set(args...);

    return send(r);
}

} // namespace Requests

#endif // REQUESTS_SESSION_IPP