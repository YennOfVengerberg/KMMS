#ifndef IO_HPP
#define IO_HPP

#include <iostream>

namespace yenni {
    void print(const char *text, int *array, const int array_size);
    void input(const char *text, int &n);
}
#endif