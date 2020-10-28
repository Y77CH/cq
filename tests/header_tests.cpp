#include <gtest/gtest.h>

#include "requests/header.hpp"

TEST( Header, Enum )
{
    requests::header h {requests::header::host, "example.com"};

    EXPECT_EQ( h.name(),           requests::header::host  );
    EXPECT_EQ( h.name().as_enum(), requests::header::host  );
    EXPECT_EQ( h.name().as_string(),                "host" );

    EXPECT_EQ( h.value(), "example.com" );

    EXPECT_EQ( h.as_string(), "host: example.com");
}

TEST( Header, String )
{
    requests::header h {"Authorization", "Bearer 12345"};

    EXPECT_EQ( h.name(),           requests::header::authorization  );
    EXPECT_EQ( h.name().as_enum(), requests::header::authorization  );
    EXPECT_EQ( h.name().as_string(),                "authorization" );

    EXPECT_EQ( h.value(), "Bearer 12345" );

    EXPECT_EQ( h.as_string(), "authorization: Bearer 12345");
}

TEST( Header, NotSupportedString )
{
    EXPECT_THROW(requests::header("a", "b"), std::invalid_argument);
}


int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}