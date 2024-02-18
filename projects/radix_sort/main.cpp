#include <iostream>
#include <random>

namespace EAbrakhin {
	void sort_by_radix(int* const arr, const int arr_size);
}

int main() {
    std::setlocale(LC_ALL, "");

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

namespace EAbrakhin {
	void sort_by_radix(int* const arr, const int arr_size) {
		int max = arr[0];
		for (int i = 1; i < arr_size; i++) {
			if (arr[i] > max) {
				max = arr[i];
			}
		}

		for (int digit = 1; max / digit > 0; digit *= 10) {
			int* output = new int[arr_size];
			int count[10] = { 0 };

			for (int i = 0; i < arr_size; i++) {
				count[(arr[i] / digit) % 10]++;
			}

			for (int i = 1; i < 10; i++) {
				count[i] += count[i - 1];
			}

			for (int i = arr_size - 1; i >= 0; i--) {
				output[count[(arr[i] / digit) % 10] - 1] = arr[i];
				count[(arr[i] / digit) % 10]--;
			}

			for (int i = 0; i < arr_size; i++) {
				arr[i] = output[i];
			}

			delete[] output;
		}
	}
}
