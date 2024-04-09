#include "merge_sort.hpp"

void EAbrakhin::merge(int* arr, const int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int* left = new int[n1];
    int* right = new int[n2];
    for (int i = 0; i < n1; i++) {
        left[i] = arr[low + i];
    }
    for (int j = 0; j < n2; j++) {
        right[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    while (i < n1) {
        arr[k++] = left[i++];
    }
    while (j < n2) {
        arr[k++] = right[j++];
    }

    delete[] left;
    delete[] right;
}

void EAbrakhin::merge_sort(int* const arr, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        EAbrakhin::merge_sort(arr, low, mid);
        EAbrakhin::merge_sort(arr, mid + 1, high);
        EAbrakhin::merge(arr, low, mid, high);
    }
}
