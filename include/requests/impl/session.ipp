#ifndef REQUESTS_IMPL_SESSION_IPP
#define REQUESTS_IMPL_SESSION_IPP

#include "requests/session.hpp"

namespace Requests {

template<typename ...Args>
Response Session::delet(std::string_view target, const Args & ...args)
{
    Request r {
        .method = Method::DELETE,
        .target = std::string{target}
    };

    prepare_request(r, args...);

    return send(r);
}


template<typename ...Args>
Response Session::get(std::string_view target, const Args & ...args)
{
    Request r {
        .method = Method::GET,
        .target = std::string{target}
    };

    prepare_request(r, args...);

    return send(r);
}


template<typename ...Args>
Response Session::head(std::string_view target, const Args & ...args)
{
    Request r {
        .method = Method::HEAD,
        .target = std::string{target}
    };

    prepare_request(r, args...);

    return send(r);
}


template<typename ...Args>
Response Session::options(std::string_view target, const Args & ...args)
{
    Request r {
        .method = Method::OPTIONS,
        .target = std::string{target}
    };

    prepare_request(r, args...);

    return send(r);
}


template<typename ...Args>
Response Session::patch(std::string_view target, const Args & ...args)
{
    Request r {
        .method = Method::PATCH,
        .target = std::string{target}
    };

    prepare_request(r, args...);

    return send(r);
}


template<typename ...Args>
Response Session::post(std::string_view target, const Args & ...args)
{
    Request r {
        .method = Method::POST,
        .target = std::string{target}
    };

    prepare_request(r, args...);

    return send(r);
}


template<typename ...Args>
Response Session::put(std::string_view target, const Args & ...args)
{
    Request r {
        .method = Method::PUT,
        .target = std::string{target}
    };

    prepare_request(r, args...);

    return send(r);
}



template<typename T, typename ...Args>
void Session::prepare_request(Request &r, const T &t, const Args & ...args) const noexcept
{
    r.set(t);
    prepare_request(r, args...);
}

} // namespace Requests

#endif // REQUESTS_IMPL_SESSION_IPP