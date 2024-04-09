#include "heap_sort.hpp"

namespace {
    void swap(int& x, int& y) {
        int temp = x;
        x = y;
        y = temp;
    }
}

void EAbrakhin::heapify(int* const arr, int size, int i) {
    int largest = i;
    int left_child = 2 * i + 1;
    int right_child = 2 * i + 2;

    if (left_child < size && arr[left_child] > arr[largest])
        largest = left_child;
    if (right_child < size && arr[right_child] > arr[largest])
        largest = right_child;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        EAbrakhin::heapify(arr, size, largest);
    }
}

void EAbrakhin::heap_sort(int* const arr, int size) {
    for (int i = size / 2 - 1; i >= 0; --i) {
        EAbrakhin::heapify(arr, size, i);
    }

    for (int i = size - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        EAbrakhin::heapify(arr, i, 0);
    }
}
