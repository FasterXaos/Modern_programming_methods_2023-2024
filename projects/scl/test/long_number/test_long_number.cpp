#include <gtest/gtest.h>

#include "long_number.hpp"

class LongNumberFixture : public testing::Test {
public:
    EAbrakhin::LongNumber nothing;
    EAbrakhin::LongNumber zero = EAbrakhin::LongNumber("0");
    EAbrakhin::LongNumber one = EAbrakhin::LongNumber("1");
    EAbrakhin::LongNumber two = EAbrakhin::LongNumber("2");
    EAbrakhin::LongNumber five = EAbrakhin::LongNumber("5");
    EAbrakhin::LongNumber minusOne = EAbrakhin::LongNumber("-1");
    EAbrakhin::LongNumber bigNum = EAbrakhin::LongNumber("12345678901234567890");
    const char* str = "123";
};

// Constructors

//TODO

// Assignment operator

//TODO

// Comparison operators

TEST_F(LongNumberFixture, EqualityOperator) {
    EAbrakhin::LongNumber oneCopy("1");
    ASSERT_TRUE(one == oneCopy);
    ASSERT_FALSE(one == minusOne);
    ASSERT_FALSE(one == two);
}

TEST_F(LongNumberFixture, GreaterThanOperator) {
    ASSERT_TRUE(two > one);
    ASSERT_TRUE(zero > minusOne);
    ASSERT_FALSE(one > two);
}

TEST_F(LongNumberFixture, LessThanOperator) {
    ASSERT_TRUE(one < two);
    ASSERT_FALSE(zero < minusOne);
    ASSERT_FALSE(two < one);
}

// Arithmetic operators

TEST_F(LongNumberFixture, AdditionOperator) {
    EAbrakhin::LongNumber sum = one + two;
    ASSERT_EQ(EAbrakhin::LongNumber("3"), sum);
    ASSERT_FALSE(sum.is_negative());
}

TEST_F(LongNumberFixture, SubtractionOperator) {
    EAbrakhin::LongNumber difference = one - two;
    ASSERT_EQ(minusOne, difference);
    ASSERT_TRUE(difference.is_negative());
}

TEST_F(LongNumberFixture, MultiplicationOperator) {
    EAbrakhin::LongNumber product = one * two;
    ASSERT_EQ(two, product);
    ASSERT_FALSE(product.is_negative());
}

TEST_F(LongNumberFixture, DivisionOperator) {
    EAbrakhin::LongNumber dividend("10");
    EAbrakhin::LongNumber divisor("2");
    EAbrakhin::LongNumber quotient = dividend / divisor;
    ASSERT_EQ(five, quotient);
    ASSERT_FALSE(quotient.is_negative());
}

TEST_F(LongNumberFixture, ModulusOperator) {
    EAbrakhin::LongNumber dividend("10");
    EAbrakhin::LongNumber divisor("3");
    EAbrakhin::LongNumber remainder = dividend % divisor;
    ASSERT_EQ(one, remainder);
    ASSERT_FALSE(remainder.is_negative());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
