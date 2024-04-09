#include "radix_sort.hpp"

void EAbrakhin::radix_sort(unsigned int* const arr, int size) {
    int max = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    for (int digit = 1; max / digit > 0; digit *= 10) {
        int* output = new int[size];
        int count[10] = { 0 };

        for (int i = 0; i < size; ++i) {
            count[(arr[i] / digit) % 10]++;
        }

        for (int i = 1; i < 10; ++i) {
            count[i] += count[i - 1];
        }

        for (int i = size - 1; i >= 0; --i) {
            output[count[(arr[i] / digit) % 10] - 1] = arr[i];
            count[(arr[i] / digit) % 10]--;
        }

        for (int i = 0; i < size; ++i) {
            arr[i] = output[i];
        }

        delete[] output;
    }
}
