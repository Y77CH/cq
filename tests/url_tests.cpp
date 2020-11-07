#include <gtest/gtest.h>

#include "requests/url.hpp"

TEST( URL, BasicHTPP )
{
    requests::url url {"HTTP://WWW.exAmplE.cOm"};

    EXPECT_EQ( url.scheme, requests::url::scheme_t::http );
    EXPECT_EQ( url.host, "www.example.com" );
    EXPECT_EQ( url.port, 80 );
    EXPECT_EQ( url.path, "/" );
    EXPECT_EQ( url.query, "" );
    EXPECT_EQ( url.fragment, "" );

    EXPECT_EQ( url.as_string(), "http://www.example.com:80/");
}

TEST( URL, DefaultPort )
{
    requests::url url {"http://www.example.com:8080"};

    EXPECT_EQ( url.scheme, requests::url::scheme_t::http );
    EXPECT_EQ( url.host, "www.example.com" );
    EXPECT_EQ( url.port, 8080 );
    EXPECT_EQ( url.path, "/" );
    EXPECT_EQ( url.query, "" );
    EXPECT_EQ( url.fragment, "" );

    EXPECT_EQ( url.as_string(), "http://www.example.com:8080/");
}

TEST( URL, BasicHTTPS )
{
    requests::url url {"https://www.example.com"};

    EXPECT_EQ( url.scheme, requests::url::scheme_t::https );
    EXPECT_EQ( url.host, "www.example.com" );
    EXPECT_EQ( url.port, 443 );
    EXPECT_EQ( url.path, "/" );
    EXPECT_EQ( url.query, "" );
    EXPECT_EQ( url.fragment, "" );

    EXPECT_EQ( url.as_string(), "https://www.example.com:443/");
}

TEST( URL, Path )
{
    requests::url url {"https://www.example.com/user/0/data.dat"};

    EXPECT_EQ( url.scheme, requests::url::scheme_t::https );
    EXPECT_EQ( url.host, "www.example.com" );
    EXPECT_EQ( url.port, 443 );
    EXPECT_EQ( url.path, "/user/0/data.dat" );
    EXPECT_EQ( url.query, "" );
    EXPECT_EQ( url.fragment, "" );

    EXPECT_EQ( url.as_string(), "https://www.example.com:443/user/0/data.dat");
}

TEST( URL, Query )
{
    requests::url url {"https://www.example.com/users?sort=age&show=10"};

    EXPECT_EQ( url.scheme, requests::url::scheme_t::https );
    EXPECT_EQ( url.host, "www.example.com" );
    EXPECT_EQ( url.port, 443 );
    EXPECT_EQ( url.path, "/users" );
    EXPECT_EQ( url.query, "sort=age&show=10" );
    EXPECT_EQ( url.fragment, "" );

    EXPECT_EQ( url.as_string(), "https://www.example.com:443/users?sort=age&show=10");
}

TEST( URL, Fragment )
{
    requests::url url {"https://www.example.com/page#header"};

    EXPECT_EQ( url.scheme, requests::url::scheme_t::https );
    EXPECT_EQ( url.host, "www.example.com" );
    EXPECT_EQ( url.port, 443 );
    EXPECT_EQ( url.path, "/page" );
    EXPECT_EQ( url.query, "" );
    EXPECT_EQ( url.fragment, "header" );

    EXPECT_EQ( url.as_string(), "https://www.example.com:443/page#header");
}

TEST( URL, Everything )
{
    requests::url url {"https://www.example.com/news?id=12345#text"};

    EXPECT_EQ( url.scheme, requests::url::scheme_t::https );
    EXPECT_EQ( url.host, "www.example.com" );
    EXPECT_EQ( url.port, 443 );
    EXPECT_EQ( url.path, "/news" );
    EXPECT_EQ( url.query, "id=12345" );
    EXPECT_EQ( url.fragment, "text" );

    EXPECT_EQ( url.as_string(), "https://www.example.com:443/news?id=12345#text");
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}