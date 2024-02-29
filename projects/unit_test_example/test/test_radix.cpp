#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "radix_sort.hpp"

TEST(ArraysEqual, AnyElementsCount) {
	int actual[] = { 1, 8, 2, 5, 3, 11 };
	const int size = sizeof(actual) / sizeof(actual[0]);
	EAbrakhin::sort_by_radix(actual, size);
	int expected[] = { 1, 2, 3, 5, 8, 11 };
	
	ASSERT_EQ(sizeof(expected) / sizeof(expected[0]), size)
		<< "Разные размеры ожидаемого и отсортированного массивов";
	
	for (int i = 0; i < size; ++i) {
		ASSERT_EQ(expected[i], actual[i]) 
			<< "Массив ожидаемый и отсортировнный отличаются в элементе с индексом "
			<< i;
	}
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
