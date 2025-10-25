#include <random>
#include "io.hpp"
#include "sort.hpp"

int main() {
    int array_size;
    int num_limit;
    yenni::input("Введите размер ", array_size);
    yenni::input("Введите максимальное число ", num_limit);
    double threshold = sqrt(array_size);
    std::mt19937 mt(time(nullptr));

    int *array = new int[array_size];
    for(int i = 0; i < array_size; i++) array[i] = mt() % num_limit;

    yenni::print("До сортировки ", array, array_size);
    yenni::modified_merge_sort(array, 0, array_size - 1, threshold, array_size);
    yenni::print("После сортировки ", array, array_size); 
}