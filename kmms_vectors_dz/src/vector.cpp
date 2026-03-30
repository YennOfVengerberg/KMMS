#include "vector.hpp"

#include <iostream>

using yenni::Vector;

template<typename T>
Vector<T>::Vector() {
	size = 0;
	capacity = START_CAPACITY;
	arr = new T[START_CAPACITY];
}

template<typename T>
Vector<T>::Vector(T input_arr[], std::size_t input_size) {
    size = 0;
    capacity = START_CAPACITY;
    arr = new T[capacity];
    for (std::size_t i = 0; i < input_size; ++i) {
        push_back(input_arr[i]);
    }
}

template<typename T>
Vector<T>::~Vector() {
	size = 0;
	capacity = 0;
	delete[] arr;
	arr = nullptr;
}

template<typename T>
std::size_t Vector<T>::get_size() const noexcept {
	return size;
}

template<typename T>
bool Vector<T>::has_item(const T& value) const noexcept {
	for(std::size_t iter = 0; iter < size; iter++) {
		if(arr[iter] == value) 
			return true;
	}
	return false;
}

template<typename T>
bool Vector<T>::insert(const std::size_t position, const T& value) {
	if(position > size)
		return false;

	if(capacity <= size + 1) 
		realloc_mem(capacity * 2);

	for(std::size_t shift = size - 1; shift > position; shift--)
		arr[shift + 1] = arr[shift]; 
	arr[position] = value;
	size++;
	return true;
}

template<typename T>
void Vector<T>::print() const noexcept {
	for(std::size_t iter = 0; iter < size; iter++) {
		std::cout << arr[iter];
	}
	std::cout << std::endl;
}

template<typename T>
void Vector<T>::push_back(const T& value) {
	if(size + 1 > capacity)
		realloc_mem(capacity * 2);

	arr[size] = value;
	size++;
}

template<typename T>
bool Vector<T>::remove_first_occurance(const T& value) {
	for(std::size_t iter = 0; iter < size; iter++) {
		if(arr[iter] == value) {
			for(std::size_t shift = iter; shift < size - 1; shift++ )
				arr[shift] = arr[shift + 1];
			size--;
			if(size < capacity / 2)
				realloc_mem(capacity / 2);
			return true;
		} 
	}
	
	return false;
}

template<typename T>
void Vector<T>::realloc_mem(const std::size_t new_capacity) {
	T *new_arr = new T[new_capacity];
	for(std::size_t i = 0; i < size; i++)
		new_arr[i] = arr[i];
	delete[] arr;
	arr = new_arr;
	capacity = new_capacity;
}