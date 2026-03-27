#include <gtest/gtest.h>

#include "doubly_linked_list.hpp"

using yenni::DoublyLinkedList;

DoublyLinkedList<int> global = {2, 4, 5, 1};

TEST(Init, VoidList) {
	DoublyLinkedList<int> list;
	DoublyLinkedList<int> *ptr = &list;
	EXPECT_NE(ptr, nullptr);
	delete ptr;
	DoublyLinkedList<int> *ptr = &list;
	EXPECT_EQ(ptr, nullptr);
}

TEST(InitAndPrint, lvalInit) {
	int arrint[] = {1, 2, 3, 4, 5};
	float arrfloat[] = {2.4, 3.6, 1.2};
	char string[] = {'t', 'e', 's', 't'};
	DoublyLinkedList<int> intinit (arrint);
	DoublyLinkedList<float> floatinit (arrfloat);
	DoublyLinkedList<char> strinit (string);
	intinit.print();
	floatinit.print();
	strinit.print();
}

TEST(InitAndPrint, rvalInit) {
	DoublyLinkedList<int> intinit = {2, 4, 5, 1};
	DoublyLinkedList<float> floatinit = {2.1, 3.0, 2.7};
	DoublyLinkedList<char> strinit = {'t', 'e', 's', 't'};
	intinit.print();
	floatinit.print();
	strinit.print();
}



TEST(Functions, get_size) {
	size_t test_res = global.get_size();
	EXPECT_EQ(test_res, 4);
}

TEST(Functions, has_item) {
	bool test_bool = global.has_item(4);
	EXPECT_TRUE(test_bool);
}

TEST(Functions, print) {
	global.print();
}

TEST(Functions, push_back) {
	char string[] = {'t', 'e', 's', 't'};
	DoublyLinkedList<char> init (string);
	init.push_back('z');
	init.print();
}

TEST(Functions, remove_first) {
	char string[] = {'t', 'e', 'e', 's', 't'};
	DoublyLinkedList<char> init (string);
	init.remove_first_occurance('e');
	init.print();
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
