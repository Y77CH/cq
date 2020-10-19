#include <gtest/gtest.h>

#include "requests/url.hpp"

TEST( URL, Empty )
{
    requests::url empty_url;

    EXPECT_EQ( empty_url.scheme,   "" );
    EXPECT_EQ( empty_url.host,     "" );
    EXPECT_EQ( empty_url.port,      0 );
    EXPECT_EQ( empty_url.path,     "" );
    EXPECT_EQ( empty_url.query,    "" );
    EXPECT_EQ( empty_url.fragment, "" );
}


TEST( HTTP, Basic )
{
    requests::url url {"HTTP://WWW.exAmplE.cOm"};

    EXPECT_EQ( url.scheme, "http" );
    EXPECT_EQ( url.host, "www.example.com" );
    EXPECT_EQ( url.port, 80 );
    EXPECT_EQ( url.path, "/" );
    EXPECT_EQ( url.query, "" );
    EXPECT_EQ( url.fragment, "" );
}

TEST( HTTP, Port )
{
    requests::url url {"http://www.example.com:8080"};

    EXPECT_EQ( url.scheme, "http" );
    EXPECT_EQ( url.host, "www.example.com" );
    EXPECT_EQ( url.port, 8080 );
    EXPECT_EQ( url.path, "/" );
    EXPECT_EQ( url.query, "" );
    EXPECT_EQ( url.fragment, "" );
}

TEST( HTTPS, Basic )
{
    requests::url url {"https://www.example.com"};

    EXPECT_EQ( url.scheme, "https" );
    EXPECT_EQ( url.host, "www.example.com" );
    EXPECT_EQ( url.port, 443 );
    EXPECT_EQ( url.path, "/" );
    EXPECT_EQ( url.query, "" );
    EXPECT_EQ( url.fragment, "" );
}

TEST( HTTPS, Path )
{
    requests::url url {"https://www.example.com/user/0/data.dat"};

    EXPECT_EQ( url.scheme, "https" );
    EXPECT_EQ( url.host, "www.example.com" );
    EXPECT_EQ( url.port, 443 );
    EXPECT_EQ( url.path, "/user/0/data.dat" );
    EXPECT_EQ( url.query, "" );
    EXPECT_EQ( url.fragment, "" );
}

TEST( HTTPS, Query )
{
    requests::url url {"https://www.example.com/users?sort=age&show=10"};

    EXPECT_EQ( url.scheme, "https" );
    EXPECT_EQ( url.host, "www.example.com" );
    EXPECT_EQ( url.port, 443 );
    EXPECT_EQ( url.path, "/users" );
    EXPECT_EQ( url.query, "sort=age&show=10" );
    EXPECT_EQ( url.fragment, "" );
}

TEST( HTTPS, Fragment )
{
    requests::url url {"https://www.example.com/page#header"};

    EXPECT_EQ( url.scheme, "https" );
    EXPECT_EQ( url.host, "www.example.com" );
    EXPECT_EQ( url.port, 443 );
    EXPECT_EQ( url.path, "/page" );
    EXPECT_EQ( url.query, "" );
    EXPECT_EQ( url.fragment, "header" );
}

TEST( HTTPS, Everything )
{
    requests::url url {"https://www.example.com/news?id=12345#text"};

    EXPECT_EQ( url.scheme, "https" );
    EXPECT_EQ( url.host, "www.example.com" );
    EXPECT_EQ( url.port, 443 );
    EXPECT_EQ( url.path, "/news" );
    EXPECT_EQ( url.query, "id=12345" );
    EXPECT_EQ( url.fragment, "text" );
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}