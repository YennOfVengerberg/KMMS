#ifndef SORTS_HPP
#define SORTS_HPP

namespace yenni {
    void merge(int *array, int left, int mid, int right);
    void insertion_sort(int *array, const int array_size);
    void modified_merge_sort(int *array, int left, int right, int threshold, const int array_size);
}
#endif