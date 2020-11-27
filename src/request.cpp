#include "requests/request.hpp"

void Requests::Request::set(const Auth &auth) noexcept
{
    headers["authorization"] = "Basic " + auth.to_base64();
}

void Requests::Request::set(const Data &data) noexcept
{
    headers["content-type"] = "application/x-www-form-urlencoded";

    if (data.empty()) { return; }

    body = "";
    for (const auto &[k, v] : data)
    {
        body += k + "=" + v + "&";
    }
    body.pop_back();
}

void Requests::Request::set(const Fragment &f) noexcept
{
    target.fragment = f;
}

void Requests::Request::set(const Header &h) noexcept
{
    headers[h.name] = h.value;
}

void Requests::Request::set(const Headers &hs) noexcept
{
    for (const auto &[h, v] : hs)
    {
        headers[h] = v;
    }
}

void Requests::Request::set(const Json &j) noexcept
{
    headers["content-type"] = "application/json";

    body = j;
}

void Requests::Request::set(const Query &q) noexcept
{
    if (q.empty()) { return; }

    for (const auto &[k, v] : q)
    {
        target.query += k + "=" + v + "&";
    }
    target.query.pop_back();
}

void Requests::Request::set(const Text &t) noexcept
{
    headers["content-type"] = "text/plain";
    body = t;
}