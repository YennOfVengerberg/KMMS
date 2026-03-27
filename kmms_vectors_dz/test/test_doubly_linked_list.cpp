#include <gtest/gtest.h>

#include "doubly_linked_list.hpp"

using yenni::DoublyLinkedList;

TEST(Init, VoidList) {
	DoublyLinkedList<int> list;
}

TEST(Init, CopyInit) {

}

TEST(Init, MoveOperatorInit) {

}

TEST(Init, Destructor) {

}

TEST(Functions, get_size) {

}

TEST(Functions, has_item) {

}

TEST(Functions, print) {

}

TEST(Functions, push_back) {

}

TEST(Functions, remove_first) {

}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
