#include "io.hpp"

void yenni::print(const char *text, int *array, const int array_size) {
    std::cout << text << std::endl;
    for(int i = 0; i < array_size; i++) {
        std::cout << *(array+i) << " ";
    }
    std::cout << std::endl;
}

void yenni::input(const char *text, int &n) {
    std::cout << text << std::endl;
    std::cin >> n;
}