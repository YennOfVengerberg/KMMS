#pragma once

#include <cstddef>
		
namespace yenni {
	template <typename T> 
	class Vector {
		private:
			static const std::size_t START_CAPACITY;

			T* arr = nullptr;
			std::size_t capacity = START_CAPACITY;
			std::size_t size = 0;

		public:
			Vector();
			Vector(T arr[]);
			// Vector(std::initializer_list<T> arr);
			Vector(const Vector&) = delete;
			Vector& operator = (const Vector&) = delete;
			~Vector();
			
			std::size_t get_size() const noexcept;
			bool has_item(const T& value) const noexcept;
			bool insert(const std::size_t position, const T& value);
			void print() const noexcept;
			void push_back(const T& value);
			bool remove_first_occurance(const T& value);
	};
}
