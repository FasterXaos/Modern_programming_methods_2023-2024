#include "quick_sort.hpp"

namespace {
    void swap(int& x, int& y) {
        int temp = x;
        x = y;
        y = temp;
    }
}

void EAbrakhin::quick_sort(int* array, int low, int high) {
    if (low < high) {
        int pivot = array[high];
        int l = low;
        for (int i = low; i < high; ++i) {
            if (array[i] < pivot)
                swap(array[l++], array[i]);
        }
        swap(array[l], array[high]);

        EAbrakhin::quick_sort(array, low, l - 1);
        EAbrakhin::quick_sort(array, l + 1, high);
    }
}
