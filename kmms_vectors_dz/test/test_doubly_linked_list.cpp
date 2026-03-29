#include <gtest/gtest.h>

#include "doubly_linked_list.hpp"

using yenni::DoublyLinkedList;

int arr[] = {2, 4, 5, 1};
int arr2[] = {};
DoublyLinkedList<int> global(arr, sizeof(arr)/sizeof(int));
DoublyLinkedList<int> global2(arr2, sizeof(arr2)/sizeof(int));

TEST(Init, VoidList) {
	DoublyLinkedList<int> list;
	DoublyLinkedList<int> *ptr = &list;
	EXPECT_NE(ptr, nullptr);
}

// TEST(InitAndPrint, lvalInit) {
// 	int arrint[] = {1, 2, 3, 4, 5};
// 	float arrfloat[] = {2.4, 3.6, 1.2};
// 	char string[] = {'t', 'e', 's', 't'};
// 	DoublyLinkedList<int> intinit (arrint, sizeof(arrint)/sizeof(int));
// 	DoublyLinkedList<float> floatinit (arrfloat, sizeof(arrfloat)/sizeof(float));
// 	DoublyLinkedList<char> strinit (string, sizeof(string)/sizeof(char));
// 	intinit.print();
// 	floatinit.print();
// 	strinit.print();
// }

// TEST(InitAndPrint, rvalInit) {
// 	DoublyLinkedList<int> intinit = {2, 4, 5, 1};
// 	DoublyLinkedList<float> floatinit = {2.1, 3.0, 2.7};
// 	DoublyLinkedList<char> strinit = {'t', 'e', 's', 't'};
// 	intinit.print();
// 	floatinit.print();
// 	strinit.print();
// }



TEST(Functions, get_size) {
	size_t test_res = global.get_size();
	size_t test_res2 = global2.get_size();
	EXPECT_EQ(test_res2, 0) << test_res2;
	EXPECT_EQ(test_res, 4) << test_res;
	std::cout << test_res << std::endl;
	std::cout << test_res2 << std::endl;
}

TEST(Functions, has_item) {
	bool test_bool = global.has_item(4);
	bool test_bool2 = global.has_item(12);
	bool test_bool3 = global2.has_item(0);
	EXPECT_TRUE(test_bool) << test_bool;
	EXPECT_FALSE(test_bool2) << test_bool2;
	EXPECT_FALSE(test_bool3) << test_bool3;
	std::cout << test_bool << std::endl << test_bool2 << std::endl << test_bool3 << std::endl;
}

TEST(Functions, print) {
	global.print();
	global2.print();
}

TEST(Functions, push_back) {
	char string[] = {'t', 'e', 's', 't'};
	DoublyLinkedList<char> init (string, sizeof(string)/sizeof(char));
	init.print();
	init.push_back('z');
	init.print();
}

TEST(Functions, remove_first) {
	char string[] = {'t', 'e', 'e', 's', 't'};
	DoublyLinkedList<char> init (string, sizeof(string)/sizeof(char));
	init.print();
	init.remove_first_occurance('e');
	init.print();
	init.remove_first_occurance('e');
	init.print();
	init.remove_first_occurance('t');
	init.print();
	std::cout << init.remove_first_occurance('z') << std::endl;
	init.print();
}

TEST(Functions, remove_first_for_void) {
	char string[] = {'t'};
	DoublyLinkedList<char> init (string, sizeof(string)/sizeof(char));
	init.print();
	init.remove_first_occurance('t');
	init.print();
	init.remove_first_occurance('t');
	init.print();
	
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
