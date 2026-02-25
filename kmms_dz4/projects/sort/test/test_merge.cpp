//#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "sort.hpp"
#include "io.hpp"

TEST(ArraysEquality, Equal) {
    const int size = 10;
    int given[size] = {12, 53, 0, 7, 11, 12, 11, 3, 4, 5};
    yenni::modified_merge_sort(given, 0, size - 1, 5, 10);
    int expected[size] = {0, 3, 4, 5, 7, 11, 11, 12, 12, 53}; // специально неправильно

    for(int i = 0; i < size; i++ ){
        ASSERT_EQ(given[i], expected[i])
            << "неравные значения в индексе " << i;
    }
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
