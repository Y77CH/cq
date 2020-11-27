#include <gtest/gtest.h>

#include "requests/api.hpp"

TEST( HTTP, Delete )
{
    Requests::Response res = Requests::delet(
        "http://httpbin.org/delete",
        Requests::Header{"Accept", "application/json"},
        Requests::Text{"data in text/plain form"}
    );

    std::cout << res.reason << " [" << res.status_code << "]\n";
    for (const auto &[h, v] : res.headers)
    {
        std::cout << h << ": " << v << "\n";
    }
    std::cout << "\n";
    std::cout << res.text << "\n";
}

TEST( HTTP, Get )
{
    Requests::Response res = Requests::get(
        "http://httpbin.org/get",
        Requests::Header{"Accept", "application/json"},
        Requests::Query{{"key", "value"}},
        Requests::Fragment{"body"}
    );

    std::cout << res.reason << " [" << res.status_code << "]\n";
    for (const auto &[h, v] : res.headers)
    {
        std::cout << h << ": " << v << "\n";
    }
    std::cout << "\n";
    std::cout << res.text << "\n";
}

TEST( HTTP, Patch )
{
    Requests::Response res = Requests::patch(
        "http://httpbin.org/patch",
        Requests::Header{"Accept", "application/json"},
        Requests::Data{
            {"info", "data in application/x-www-form-urlencoded form"},
            {"key", "value"}
        }
    );

    std::cout << res.reason << " [" << res.status_code << "]\n";
    for (const auto &[h, v] : res.headers)
    {
        std::cout << h << ": " << v << "\n";
    }
    std::cout << "\n";
    std::cout << res.text << "\n";
}

TEST( HTTP, Post )
{
    Requests::Response res = Requests::post(
        "http://httpbin.org/post",
        Requests::Header{"Accept", "application/json"},
        Requests::Json{"{\"note\":\"Requests::Json is a string, not real json object\"}"}
    );

    std::cout << res.reason << " [" << res.status_code << "]\n";
    for (const auto &[h, v] : res.headers)
    {
        std::cout << h << ": " << v << "\n";
    }
    std::cout << "\n";
    std::cout << res.text << "\n";
}

TEST( HTTP, Put )
{
    Requests::Response res = Requests::put(
        "http://httpbin.org/put",
        Requests::Header{"Accept", "application/json"}
    );

    std::cout << res.reason << " [" << res.status_code << "]\n";
    for (const auto &[h, v] : res.headers)
    {
        std::cout << h << ": " << v << "\n";
    }
    std::cout << "\n";
    std::cout << res.text << "\n";
}


TEST( HTTPS, Delete )
{
    Requests::Response res = Requests::delet(
        "https://httpbin.org/delete",
        Requests::Header{"Accept", "application/json"}
    );

    std::cout << res.reason << " [" << res.status_code << "]\n";
    for (const auto &[h, v] : res.headers)
    {
        std::cout << h << ": " << v << "\n";
    }
    std::cout << "\n";
    std::cout << res.text << "\n";
}

TEST( HTTPS, Get )
{
    Requests::Response res = Requests::get(
        "https://httpbin.org/get",
        Requests::Header{"Accept", "application/json"}
    );

    std::cout << res.reason << " [" << res.status_code << "]\n";
    for (const auto &[h, v] : res.headers)
    {
        std::cout << h << ": " << v << "\n";
    }
    std::cout << "\n";
    std::cout << res.text << "\n";
}

TEST( HTTPS, Patch )
{
    Requests::Response res = Requests::patch(
        "https://httpbin.org/patch",
        Requests::Header{"Accept", "application/json"}
    );

    std::cout << res.reason << " [" << res.status_code << "]\n";
    for (const auto &[h, v] : res.headers)
    {
        std::cout << h << ": " << v << "\n";
    }
    std::cout << "\n";
    std::cout << res.text << "\n";
}

TEST( HTTPS, Post )
{
    Requests::Response res = Requests::post(
        "https://httpbin.org/post",
        Requests::Header{"Accept", "application/json"}
    );

    std::cout << res.reason << " [" << res.status_code << "]\n";
    for (const auto &[h, v] : res.headers)
    {
        std::cout << h << ": " << v << "\n";
    }
    std::cout << "\n";
    std::cout << res.text << "\n";
}

TEST( HTTPS, Put )
{
    Requests::Response res = Requests::put(
        "https://httpbin.org/put",
        Requests::Header{"Accept", "application/json"}
    );

    std::cout << res.reason << " [" << res.status_code << "]\n";
    for (const auto &[h, v] : res.headers)
    {
        std::cout << h << ": " << v << "\n";
    }
    std::cout << "\n";
    std::cout << res.text << "\n";
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}