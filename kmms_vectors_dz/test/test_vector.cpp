#include <gtest/gtest.h>

#include "vector.hpp"

using yenni::Vector;

Vector<int> global = {1, 2, 3, 4, 5};

TEST(Init, VoidVector) {
	Vector<int> vec;
	Vector<int> *ptr = &vec;
	EXPECT_NE(ptr, nullptr);
}

TEST(Init, Destructor) {

}

TEST(InitAndPrint, lvalInit) {
	int arrint[] = {1, 2, 3, 4, 5};
	float arrfloat[] = {2.4, 3.6, 1.2};
	char string[] = {'t', 'e', 's', 't'};
	Vector<int> intinit (arrint);
	Vector<float> floatinit (arrfloat);
	Vector<char> strinit (string);
	intinit.print();
	floatinit.print();
	strinit.print();
}

TEST(InitAndPrint, rvalInit) {
	Vector<int> intinit = {2, 4, 5, 1};
	Vector<float> floatinit = {2.1, 3.0, 2.7};
	Vector<char> strinit = {'t', 'e', 's', 't'};
	intinit.print();
	floatinit.print();
	strinit.print();
}

TEST(Functions, get_size) {
	size_t test_res = global.get_size();
	EXPECT_EQ(test_res, 5);
}

TEST(Functions, has_item) {
	bool test_bool = global.has_item(4);
	EXPECT_TRUE(test_bool);
}

TEST(Functions, insert) {
	Vector<int> intinit = {2, 4, 5, 1};
	intinit.insert(2, 13);
	intinit.print();
}

TEST(Functions, push_back) {
	char string[] = {'t', 'e', 's', 't'};
	Vector<char> init (string);
	init.push_back('z');
	init.print();
}

TEST(Functions, remove_first) {
	char string[] = {'t', 'e', 'e', 's', 't'};
	Vector<char> init (string);
	init.remove_first_occurance('e');
	init.print();
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
