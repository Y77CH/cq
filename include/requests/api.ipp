#ifndef REQUESTS_API_IPP
#define REQUESTS_API_IPP

#include "requests/api.hpp"

#include "requests/session.hpp"


namespace Requests {

template<typename ...Args>
Response delet(const Url &url, const Args & ...args)
{
    Url base_url;
    base_url.scheme = url.scheme;
    base_url.host = url.host;
    base_url.port = url.port;

    Session s {.base_url = base_url};

    return s.delet(url, args...);
}


template<typename ...Args>
Response get(const Url &url, const Args & ...args)
{
    Url base_url;
    base_url.scheme = url.scheme;
    base_url.host = url.host;
    base_url.port = url.port;

    Session s {.base_url = base_url};

    return s.get(url, args...);
}


template<typename ...Args>
Response head(const Url &url, const Args & ...args)
{
    Url base_url;
    base_url.scheme = url.scheme;
    base_url.host = url.host;
    base_url.port = url.port;

    Session s {.base_url = base_url};

    return s.head(url, args...);
}


template<typename ...Args>
Response options(const Url &url, const Args & ...args)
{
    Url base_url;
    base_url.scheme = url.scheme;
    base_url.host = url.host;
    base_url.port = url.port;

    Session s {.base_url = base_url};

    return s.options(url, args...);
}


template<typename ...Args>
Response patch(const Url &url, const Args & ...args)
{
    Url base_url;
    base_url.scheme = url.scheme;
    base_url.host = url.host;
    base_url.port = url.port;

    Session s {.base_url = base_url};

    return s.patch(url, args...);
}


template<typename ...Args>
Response post(const Url &url, const Args & ...args)
{
    Url base_url;
    base_url.scheme = url.scheme;
    base_url.host = url.host;
    base_url.port = url.port;

    Session s {.base_url = base_url};

    return s.post(url, args...);
}


template<typename ...Args>
Response put(const Url &url, const Args & ...args)
{
    Url base_url;
    base_url.scheme = url.scheme;
    base_url.host = url.host;
    base_url.port = url.port;

    Session s {.base_url = base_url};

    return s.put(url, args...);
}

} // namespace Requests

#endif // REQUESTS_API_IPP