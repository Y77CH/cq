#include <gtest/gtest.h>

#include "requests/url.hpp"

TEST( URL, Empty )
{
    requests::url url;

    EXPECT_EQ( url.scheme(),   requests::url::schemes::none );
    EXPECT_EQ( url.host(),     "" );
    EXPECT_EQ( url.port(),      0 );
    EXPECT_EQ( url.path(),     "" );
    EXPECT_EQ( url.query(),    "" );
    EXPECT_EQ( url.fragment(), "" );

    EXPECT_EQ( url.str(), "");
}


TEST( HTTP, Basic )
{
    requests::url url {"HTTP://WWW.exAmplE.cOm"};

    EXPECT_EQ( url.scheme(), requests::url::schemes::http );
    EXPECT_EQ( url.host(), "www.example.com" );
    EXPECT_EQ( url.port(), 80 );
    EXPECT_EQ( url.path(), "/" );
    EXPECT_EQ( url.query(), "" );
    EXPECT_EQ( url.fragment(), "" );

    EXPECT_EQ( url.str(), "http://www.example.com:80/");
}

TEST( HTTP, Port )
{
    requests::url url {"http://www.example.com:8080"};

    EXPECT_EQ( url.scheme(), requests::url::schemes::http );
    EXPECT_EQ( url.host(), "www.example.com" );
    EXPECT_EQ( url.port(), 8080 );
    EXPECT_EQ( url.path(), "/" );
    EXPECT_EQ( url.query(), "" );
    EXPECT_EQ( url.fragment(), "" );

    EXPECT_EQ( url.str(), "http://www.example.com:8080/");
}

TEST( HTTPS, Basic )
{
    requests::url url {"https://www.example.com"};

    EXPECT_EQ( url.scheme(), requests::url::schemes::https );
    EXPECT_EQ( url.host(), "www.example.com" );
    EXPECT_EQ( url.port(), 443 );
    EXPECT_EQ( url.path(), "/" );
    EXPECT_EQ( url.query(), "" );
    EXPECT_EQ( url.fragment(), "" );

    EXPECT_EQ( url.str(), "https://www.example.com:443/");
}

TEST( HTTPS, Path )
{
    requests::url url {"https://www.example.com/user/0/data.dat"};

    EXPECT_EQ( url.scheme(), requests::url::schemes::https );
    EXPECT_EQ( url.host(), "www.example.com" );
    EXPECT_EQ( url.port(), 443 );
    EXPECT_EQ( url.path(), "/user/0/data.dat" );
    EXPECT_EQ( url.query(), "" );
    EXPECT_EQ( url.fragment(), "" );

    EXPECT_EQ( url.str(), "https://www.example.com:443/user/0/data.dat");
}

TEST( HTTPS, Query )
{
    requests::url url {"https://www.example.com/users?sort=age&show=10"};

    EXPECT_EQ( url.scheme(), requests::url::schemes::https );
    EXPECT_EQ( url.host(), "www.example.com" );
    EXPECT_EQ( url.port(), 443 );
    EXPECT_EQ( url.path(), "/users" );
    EXPECT_EQ( url.query(), "sort=age&show=10" );
    EXPECT_EQ( url.fragment(), "" );

    EXPECT_EQ( url.str(), "https://www.example.com:443/users?sort=age&show=10");
}

TEST( HTTPS, Fragment )
{
    requests::url url {"https://www.example.com/page#header"};

    EXPECT_EQ( url.scheme(), requests::url::schemes::https );
    EXPECT_EQ( url.host(), "www.example.com" );
    EXPECT_EQ( url.port(), 443 );
    EXPECT_EQ( url.path(), "/page" );
    EXPECT_EQ( url.query(), "" );
    EXPECT_EQ( url.fragment(), "header" );

    EXPECT_EQ( url.str(), "https://www.example.com:443/page#header");
}

TEST( HTTPS, Everything )
{
    requests::url url {"https://www.example.com/news?id=12345#text"};

    EXPECT_EQ( url.scheme(), requests::url::schemes::https );
    EXPECT_EQ( url.host(), "www.example.com" );
    EXPECT_EQ( url.port(), 443 );
    EXPECT_EQ( url.path(), "/news" );
    EXPECT_EQ( url.query(), "id=12345" );
    EXPECT_EQ( url.fragment(), "text" );

    EXPECT_EQ( url.str(), "https://www.example.com:443/news?id=12345#text");
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}