#include "selection_sort.hpp"

namespace {
    void swap(int& x, int& y) {
        int temp = x;
        x = y;
        y = temp;
    }
}

void EAbrakhin::selection_sort(int* const arr, int size) {
    for (int i = 0; i < size - 1; ++i) {
        int min_index = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        swap(arr[i], arr[min_index]);
    }
}
