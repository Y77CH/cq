#include <gtest/gtest.h>

#include "requests/options/method.hpp"

TEST( Method, Enum )
{
    Requests::Method m {Requests::Method::GET};

    EXPECT_EQ( m, Requests::Method::GET);
    EXPECT_EQ( m.to_string(),      "GET");
}

TEST( Method, String )
{
    Requests::Method m {"post"};

    EXPECT_EQ( m, Requests::Method::POST);
    EXPECT_EQ( m.to_string(),      "POST");
}

TEST( Method, Caps )
{
    Requests::Method m {"DELETE"};

    EXPECT_EQ( m, Requests::Method::DELETE);
    EXPECT_EQ( m.to_string(),      "DELETE");
}

TEST( Method, NotSupportedString )
{
    EXPECT_THROW(Requests::Method m {"trace"}, std::invalid_argument);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}