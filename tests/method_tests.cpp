#include <gtest/gtest.h>

#include "requests/method.hpp"

TEST( Method, Enum )
{
    requests::method m {requests::method::verbs::GET};

    EXPECT_EQ( m.str(),  "GET");
    EXPECT_EQ( m.verb(), requests::method::verbs::GET);
}

TEST( Method, String )
{
    requests::method m {"post"};

    EXPECT_EQ( m.str(),  "POST");
    EXPECT_EQ( m.verb(), requests::method::verbs::POST);
}

TEST( Method, Caps )
{
    requests::method m {"DELETE"};

    EXPECT_EQ( m.str(),  "DELETE");
    EXPECT_EQ( m.verb(), requests::method::verbs::DELETE);
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