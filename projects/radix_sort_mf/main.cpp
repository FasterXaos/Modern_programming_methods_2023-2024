#include <iostream>
#include <random>

#include "radix_sort.hpp"

int main() {
    std::mt19937 mt(time(0));
    std::uniform_int_distribution<int> dist(0, 100);

    const int arr_size = 10;
    int* arr = new int[arr_size];

    std::cout << "Массив до сортировки:";
    for (int i = 0; i < arr_size; ++i) {
        arr[i] = dist(mt);
        std::cout << ' ' << arr[i];
    }
    std::cout << std::endl;

    EAbrakhin::sort_by_radix(arr, arr_size);

    std::cout << "Массив после сортировки:";
    for (int i = 0; i < arr_size; i++) {
        std::cout << ' ' << arr[i];
    }
    std::cout << std::endl;

    system("pause");

    return 0;
}
