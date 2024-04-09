#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "bubble_sort.hpp"
#include "heap_sort.hpp"
#include "insertion_sort.hpp"
#include "merge_sort.hpp"
#include "quick_sort.hpp"
#include "radix_sort.hpp"
#include "selection_sort.hpp"
#include "shell_sort.hpp"

TEST(SortingTest, BubbleSort) {
    int array[] = {5, -3, 1, 0, -7, 9, -2, 4, -6, 2};
    const int size = sizeof(array) / sizeof(array[0]);
    EAbrakhin::bubble_sort(array, size);
    ASSERT_TRUE(std::is_sorted(array, array + size));
}

TEST(SortingTest, HeapSort) {
    int array[] = {5, -3, 1, 0, -7, 9, -2, 4, -6, 2};
    const int size = sizeof(array) / sizeof(array[0]);
    EAbrakhin::heap_sort(array, size);
    ASSERT_TRUE(std::is_sorted(array, array + size));
}

TEST(SortingTest, InsertionSort) {
    int array[] = {5, -3, 1, 0, -7, 9, -2, 4, -6, 2};
    const int size = sizeof(array) / sizeof(array[0]);
    EAbrakhin::insertion_sort(array, size);
    ASSERT_TRUE(std::is_sorted(array, array + size));
}

TEST(SortingTest, MergeSort) {
    int array[] = {5, -3, 1, 0, -7, 9, -2, 4, -6, 2};
    const int size = sizeof(array) / sizeof(array[0]);
    EAbrakhin::merge_sort(array, 0, size - 1);
    ASSERT_TRUE(std::is_sorted(array, array + size));
}

TEST(SortingTest, QuickSort) {
    int array[] = {5, -3, 1, 0, -7, 9, -2, 4, -6, 2};
    const int size = sizeof(array) / sizeof(array[0]);
    EAbrakhin::quick_sort(array, 0, size - 1);
    ASSERT_TRUE(std::is_sorted(array, array + size));
}

TEST(SortingTest, RadixSort) {
    unsigned int unsign_array[] = {5, 3, 1, 0, 7, 9, 2, 4, 6, 2};
    const int size = sizeof(unsign_array) / sizeof(unsign_array[0]);
    EAbrakhin::radix_sort(unsign_array, size);
    ASSERT_TRUE(std::is_sorted(unsign_array, unsign_array + size));
}

TEST(SortingTest, SelectionSort) {
    int array[] = {5, -3, 1, 0, -7, 9, -2, 4, -6, 2};
    const int size = sizeof(array) / sizeof(array[0]);
    EAbrakhin::selection_sort(array, size);
    ASSERT_TRUE(std::is_sorted(array, array + size));
}

TEST(SortingTest, ShellSort) {
    int array[] = {5, -3, 1, 0, -7, 9, -2, 4, -6, 2};
    const int size = sizeof(array) / sizeof(array[0]);
    EAbrakhin::shell_sort(array, size);
    ASSERT_TRUE(std::is_sorted(array, array + size));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
