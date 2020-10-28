#include <gtest/gtest.h>

#include "requests/method.hpp"

TEST( Method, Enum )
{
    requests::method m {requests::method::GET};

    EXPECT_EQ( m.as_enum(), requests::method::GET);
    EXPECT_EQ( m.as_string(), "GET");
}

TEST( Method, String )
{
    requests::method m {"post"};

    EXPECT_EQ( m.as_enum(), requests::method::POST);
    EXPECT_EQ( m.as_string(),  "POST");
}

TEST( Method, Caps )
{
    requests::method m {"DELETE"};

    EXPECT_EQ( m.as_enum(), requests::method::DELETE);
    EXPECT_EQ( m.as_string(),  "DELETE");
}

TEST( Method, NotSupportedString )
{
    EXPECT_THROW(requests::method m {"trace"}, std::invalid_argument);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}