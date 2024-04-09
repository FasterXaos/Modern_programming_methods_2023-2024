#include "bubble_sort.hpp"

namespace {
    void swap(int& x, int& y) {
        int temp = x;
        x = y;
        y = temp;
    }
}

void EAbrakhin::bubble_sort(int* const arr, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
