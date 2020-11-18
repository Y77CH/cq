#include <gtest/gtest.h>

#include "requests/options/url.hpp"

TEST( URL, BasicHTPP )
{
    Requests::Url url {"HTTP://WWW.exAmplE.cOm"};

    EXPECT_EQ( url.scheme,  Requests::Url::Scheme::http );
    EXPECT_EQ( url.host, "www.example.com" );
    EXPECT_EQ( url.port, 80 );
    EXPECT_EQ( url.path, "/" );
    EXPECT_EQ( url.query, "" );
    EXPECT_EQ( url.fragment, "" );

    EXPECT_EQ( url.to_string(), "http://www.example.com:80/");
}

TEST( URL, DefaultPort )
{
    Requests::Url url {"http://www.example.com:8080"};

    EXPECT_EQ( url.scheme, Requests::Url::Scheme::http );
    EXPECT_EQ( url.host, "www.example.com" );
    EXPECT_EQ( url.port, 8080 );
    EXPECT_EQ( url.path, "/" );
    EXPECT_EQ( url.query, "" );
    EXPECT_EQ( url.fragment, "" );

    EXPECT_EQ( url.to_string(), "http://www.example.com:8080/");
}

TEST( URL, BasicHTTPS )
{
    Requests::Url url {"https://www.example.com"};

    EXPECT_EQ( url.scheme, Requests::Url::Scheme::https );
    EXPECT_EQ( url.host, "www.example.com" );
    EXPECT_EQ( url.port, 443 );
    EXPECT_EQ( url.path, "/" );
    EXPECT_EQ( url.query, "" );
    EXPECT_EQ( url.fragment, "" );

    EXPECT_EQ( url.to_string(), "https://www.example.com:443/");
}

TEST( URL, Path )
{
    Requests::Url url {"https://www.example.com/user/0/data.dat"};

    EXPECT_EQ( url.scheme, Requests::Url::Scheme::https );
    EXPECT_EQ( url.host, "www.example.com" );
    EXPECT_EQ( url.port, 443 );
    EXPECT_EQ( url.path, "/user/0/data.dat" );
    EXPECT_EQ( url.query, "" );
    EXPECT_EQ( url.fragment, "" );

    EXPECT_EQ( url.to_string(), "https://www.example.com:443/user/0/data.dat");
}

TEST( URL, Query )
{
    Requests::Url url {"https://www.example.com/users?sort=age&show=10"};

    EXPECT_EQ( url.scheme, Requests::Url::Scheme::https );
    EXPECT_EQ( url.host, "www.example.com" );
    EXPECT_EQ( url.port, 443 );
    EXPECT_EQ( url.path, "/users" );
    EXPECT_EQ( url.query, "sort=age&show=10" );
    EXPECT_EQ( url.fragment, "" );

    EXPECT_EQ( url.to_string(), "https://www.example.com:443/users?sort=age&show=10");
}

TEST( URL, Fragment )
{
    Requests::Url url {"https://www.example.com/page#header"};

    EXPECT_EQ( url.scheme, Requests::Url::Scheme::https );
    EXPECT_EQ( url.host, "www.example.com" );
    EXPECT_EQ( url.port, 443 );
    EXPECT_EQ( url.path, "/page" );
    EXPECT_EQ( url.query, "" );
    EXPECT_EQ( url.fragment, "header" );

    EXPECT_EQ( url.to_string(), "https://www.example.com:443/page#header");
}

TEST( URL, Everything )
{
    Requests::Url url {"https://www.example.com/news?id=12345#text"};

    EXPECT_EQ( url.scheme, Requests::Url::Scheme::https );
    EXPECT_EQ( url.host, "www.example.com" );
    EXPECT_EQ( url.port, 443 );
    EXPECT_EQ( url.path, "/news" );
    EXPECT_EQ( url.query, "id=12345" );
    EXPECT_EQ( url.fragment, "text" );

    EXPECT_EQ( url.to_string(), "https://www.example.com:443/news?id=12345#text");
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}