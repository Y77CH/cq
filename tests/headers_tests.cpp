#include <gtest/gtest.h>

#include "requests/options/headers.hpp"

TEST( Header, Enum )
{
    Requests::Header h = Requests::Header::host;

    EXPECT_EQ( h,           Requests::Header::host  );
    EXPECT_EQ( h.to_string(),                "host" );
}

TEST( Header, String )
{
    auto h = Requests::Header{"User-Agent"};

    EXPECT_EQ( h,           Requests::Header::user_agent  );
    EXPECT_EQ( h.to_string(),                "user-agent" );
}

TEST( Header, NotSupportedString )
{
    EXPECT_THROW(Requests::Header{"a"}, std::invalid_argument);
}



TEST( Headers, All )
{
    Requests::Headers hs {
        {Requests::Header::authorization, "token"},
        {Requests::Header::host, "www.example.com"},
        {Requests::Header::user_agent, "Requests"}
    };
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}