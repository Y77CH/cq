#include <gtest/gtest.h>

#include "requests/headers.hpp"

TEST( Header, Enum )
{
    requests::header h = requests::header::host;

    EXPECT_EQ( h,           requests::header::host  );
    EXPECT_EQ( h.as_enum(), requests::header::host  );
    EXPECT_EQ( h.as_string(),                "host" );
}

TEST( Header, String )
{
    auto h = requests::header{"User-Agent"};

    EXPECT_EQ( h,           requests::header::user_agent  );
    EXPECT_EQ( h.as_enum(), requests::header::user_agent  );
    EXPECT_EQ( h.as_string(),                "user-agent" );
}

TEST( Header, NotSupportedString )
{
    EXPECT_THROW(requests::header{"a"}, std::invalid_argument);
}



TEST( Headers, All )
{
    requests::headers hs {
        {requests::header::authorization, "token"},
        {requests::header::host, "www.example.com"},
        {requests::header::user_agent, "LibRequests"}
    };
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}