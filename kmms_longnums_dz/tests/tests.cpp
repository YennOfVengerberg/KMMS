//#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "long_nums.hpp"

using yenni::LongNumber;

const LongNumber num_25("25");
// init
TEST(Inititalization, SimpleInitialize) {   
    LongNumber init;
    LongNumber *ptr = &init;
    ASSERT_NE(ptr, nullptr);
}

TEST(Inititalization, SimpleConcreteInitialize) {   
    LongNumber init("25");
    LongNumber *ptr = &init;
    EXPECT_NE(ptr, nullptr);
    EXPECT_EQ(init, num_25);
    ASSERT_TRUE(init == num_25);
}

TEST(Inititalization, CopyInitialize) {   
    LongNumber init("52");
    LongNumber copy = init;
    EXPECT_EQ(init, copy);

    LongNumber *ptr = &init;
    EXPECT_NE(ptr, nullptr);
    LongNumber *ptr_copy = &copy;
    EXPECT_NE(ptr, nullptr);
    
}

TEST(Inititalization, MoveInitialize) {   
    LongNumber init("52");
    LongNumber move("221");
    move = init;
    LongNumber *ptr = &move;
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(&move, ptr);
    ASSERT_EQ(move, "52");
}
// = init
TEST(Inititalization, CopyAssignInitialize) {   
    LongNumber init("52");
    LongNumber copy;
    copy = init;
    LongNumber *ptr = &copy;
    ASSERT_NE(ptr, nullptr);
    ASSERT_EQ(init, copy);
}

TEST(Inititalization, AssignMoveInitialize) {   
    LongNumber init("52");
    LongNumber move("221");
    move = init;
    LongNumber *ptr = &move;
    //EXPECT_NE(ptr, nullptr);
    ASSERT_EQ(move, init);
}

TEST(Inititalization, InitializeWithConst) {   
    LongNumber init = "52";
    LongNumber *ptr = &init;
    ASSERT_NE(ptr, nullptr);
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

TEST(Arithmetics, Plus) {
    LongNumber num1("52");
    LongNumber num2("25");
    LongNumber num3("-52");

    ASSERT_EQ(num1 + num2, LongNumber("77"));
    ASSERT_EQ(num2 + num3, LongNumber("-27"));
    ASSERT_EQ(num1 + num3, LongNumber("0"));
}

TEST(Arithmetics, Minus) {
    LongNumber num1("52");
    LongNumber num2("25");
    LongNumber num3("-52");
    ASSERT_EQ((num1 - num2), LongNumber("27"));
    ASSERT_EQ(num2 - num3, LongNumber("77"));
    ASSERT_EQ(num1 - num3, LongNumber("104"));
    ASSERT_EQ(num2 - num1, LongNumber("-27"));
}

TEST(Arithmetics, Multiplication) {
    LongNumber num1("52");
    LongNumber num2("25");
    LongNumber num3("-52");
    ASSERT_EQ((num1 * num2), LongNumber("1300"));
    ASSERT_EQ(num2 * num3, LongNumber("-1300"));
    ASSERT_EQ(num1 * num3, LongNumber("-2704"));
    ASSERT_EQ(num3 * num3, LongNumber("2704"));
}

TEST(Arithmetics, Division) {
    LongNumber num1("50");
    LongNumber num2("25");
    LongNumber num3("-50");
    ASSERT_EQ((num1 / num2), LongNumber("2"));
    ASSERT_EQ(num2 / num3, LongNumber("0"));
    ASSERT_EQ(num1 / num3, LongNumber("-1"));
}

TEST(Arithmetics, RemainderDivision) {
    LongNumber num1("50");
    LongNumber num2("25");
    LongNumber num3("-100");
    ASSERT_EQ((num1 % num2), LongNumber("0"));
    ASSERT_EQ(num2 % num3, LongNumber("-25"));
    ASSERT_EQ(num1 % num3, LongNumber("-5"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
