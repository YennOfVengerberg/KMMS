//#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "long_nums.hpp"

using namespace yenni;
// init
TEST(Inititalization, SimpleInitialize) {   
    LongNumber init;
    EXPECT_FALSE(init.is_negative());
}

TEST(Inititalization, SimpleConcreteInitialize) {   
    LongNumber init("25");
    EXPECT_FALSE(init.is_negative());
    ASSERT_EQ(init, "25");
}

TEST(Inititalization, CopyInitialize) {   
    LongNumber init("52");
    LongNumber copy = init;
    EXPECT_FALSE(init.is_negative());
    EXPECT_FALSE(copy.is_negative());
    ASSERT_EQ(init, copy);
}

TEST(Inititalization, MoveInitialize) {   
    LongNumber init("52");
    LongNumber move("221");
    move = init;
    EXPECT_TRUE(init.is_negative());
    EXPECT_FALSE(move.is_negative());
    ASSERT_EQ(move, "52");
}
// = init
TEST(Inititalization, CopyAssignInitialize) {   
    LongNumber init("52");
    LongNumber copy;
    copy = init;
    EXPECT_FALSE(init.is_negative());
    EXPECT_FALSE(copy.is_negative());
    ASSERT_EQ(init, copy);
}

TEST(Inititalization, AssignMoveInitialize) {   
    LongNumber init("52");
    LongNumber move("221");
    move = LongNumber("52");
    EXPECT_FALSE(move.is_negative());
    ASSERT_EQ(move, init);
}

TEST(Inititalization, InitializeWithConst) {   
    LongNumber init = "52";
    EXPECT_FALSE(init.is_negative());
    ASSERT_EQ(init, "52");
}
// 
TEST(Comparison, Equality_Unequality) {   
    LongNumber num1("52");
    LongNumber num2("52");
    LongNumber num3("25");
    LongNumber num4("-52");
    ASSERT_EQ(num1, num2);
    ASSERT_EQ(num4, num4);
    ASSERT_NE(num1, num4);
    ASSERT_NE(num2, num3);
    ASSERT_NE(num1, num3);
}

TEST(Comparison, Greater_Less) {   
    LongNumber num1("52");
    LongNumber num2("-52");
    LongNumber num3("25");
    ASSERT_GT(num1, num2);
    ASSERT_LT(num2, num3);
    ASSERT_GT(num1, num3);
}
