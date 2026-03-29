#include "doubly_linked_list.hpp"

#include <iostream>

using yenni::DoublyLinkedList;

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(T arr[], std::size_t size) {
    for(std::size_t i = 0; i < size; ++i) {
        push_back(arr[i]);
    }
}

// template<typename T>
// DoublyLinkedList<T>::DoublyLinkedList(std::initializer_list<T> init) {
//     for(const auto& item : init) {
//         push_back(item);
//     }
// }


template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	Node *current = begin;
    while(current != nullptr) {
        Node *next = current->next;
        delete current;
        current = next;
    }
    begin = nullptr;
    end = nullptr;
}

template<typename T>
std::size_t DoublyLinkedList<T>::get_size() const noexcept {
	std::size_t size = 0;
    Node *current = begin;
    while(current != nullptr) {
        size++;
        current = current->next;
    }
    return size;
}

template<typename T>
bool DoublyLinkedList<T>::has_item(const T& value) const noexcept {
	Node *current = begin;
    while(current != nullptr) {
        if(current->value == value) 
            return true;
        current = current->next;
    }
    return false;
}

template<typename T>
void DoublyLinkedList<T>::print() const noexcept {
	Node *current = begin;
    while(current != nullptr) {
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
    return;
}

template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
	Node *new_node = new Node(value);
    if(end == nullptr) {
        begin = new_node;
        end = new_node;
    } else {
        end->next = new_node;
        new_node->prev = end;
        end = new_node;
    }

}

template<typename T>
bool DoublyLinkedList<T>::remove_first_occurance(const T& value) noexcept {
	Node* current = begin;
    while (current != nullptr) {
        if (current->value == value) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                begin = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                end = current->prev;
            }
            delete current;
            return true;
        }
        current = current->next;
    }
    return false;
}