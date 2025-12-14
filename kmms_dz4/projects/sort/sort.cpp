#include "sort.hpp"

void yenni::merge(int *array, int left, int mid, int right) {
    int left_size = mid - left + 1;
    int right_size = right - mid;
    int *left_part = new int(left_size);
    int *right_part = new int(right_size);
    for (int i = 0; i < left_size; i++) left_part[i] = array[left + i];
    for (int j = 0; j < right_size; j++) right_part[j] = array[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    while (i < left_size && j < right_size) {
        if (left_part[i] <= right_part[j]) {
            array[k] = left_part[i];
            i++;
        } else {
            array[k] = right_part[j];
            j++;
        }
        k++;
    }
}

void yenni::insertion_sort(int *array, const int array_size) {
    for (int i = 1; i < array_size; i++) {
        int temp = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > temp) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = temp;
    }
}

void yenni::modified_merge_sort(int *array, int left, int right, int threshold, const int array_size) {
    if (right - left + 1 <= threshold) {
        insertion_sort(array, array_size);
    } else {
        if (left < right) {
            int mid = left + (right - left) / 2;
            modified_merge_sort(array, left, mid, threshold, array_size);
            modified_merge_sort(array, mid + 1, right, threshold, array_size);
            merge(array, left, mid, right);
        }
    }
}