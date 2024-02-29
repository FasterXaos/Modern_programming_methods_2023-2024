#include <gtest/gtest.h>

#include "long_number.hpp"

class LongNumberFixture : public testing::Test {
public:
    EAbrakhin::LongNumber nothing;
    EAbrakhin::LongNumber zero = EAbrakhin::LongNumber("0");
    EAbrakhin::LongNumber one = EAbrakhin::LongNumber("1");
    EAbrakhin::LongNumber two = EAbrakhin::LongNumber("2");
    EAbrakhin::LongNumber three = EAbrakhin::LongNumber("3");
    EAbrakhin::LongNumber five = EAbrakhin::LongNumber("5");
    EAbrakhin::LongNumber ten = EAbrakhin::LongNumber("10");
    EAbrakhin::LongNumber minusOne = EAbrakhin::LongNumber("-1");
    EAbrakhin::LongNumber minusTwo = EAbrakhin::LongNumber("-2");
    EAbrakhin::LongNumber minusFive = EAbrakhin::LongNumber("-5");
    EAbrakhin::LongNumber bigNum = EAbrakhin::LongNumber("12345678901234567890");
    const char* strPos = "123";
    const char* strNeg = "-123";
};

// Constructors

TEST_F(LongNumberFixture, DefaultConstructor) {
    ASSERT_EQ(1, nothing.get_digits_number());
    ASSERT_FALSE(nothing.is_negative());
}

TEST_F(LongNumberFixture, LongConstructor) {
    ASSERT_EQ(20, bigNum.get_digits_number());
    ASSERT_FALSE(bigNum.is_negative());
}

TEST_F(LongNumberFixture, StringConstructor) {
    ASSERT_EQ(3, EAbrakhin::LongNumber(strPos).get_digits_number());
    ASSERT_EQ(3, EAbrakhin::LongNumber(strNeg).get_digits_number());
    ASSERT_EQ(2, EAbrakhin::LongNumber(ten).get_digits_number());
}

TEST_F(LongNumberFixture, CopyConstructor) {
    EAbrakhin::LongNumber copiedNumber(bigNum);
    ASSERT_EQ(bigNum, copiedNumber);
}

TEST_F(LongNumberFixture, MoveConstructor) {
    EAbrakhin::LongNumber original(bigNum);
    EAbrakhin::LongNumber moved(std::move(original));
    ASSERT_EQ(bigNum, moved);
}

// Assignment operator

TEST_F(LongNumberFixture, AssignmentOperatorLong) {
    EAbrakhin::LongNumber assigned = zero;
    ASSERT_EQ(zero, assigned);
}

TEST_F(LongNumberFixture, AssignmentOperatorString) {
    EAbrakhin::LongNumber assigned = strPos;
    EAbrakhin::LongNumber str(strPos);
    ASSERT_EQ(str, assigned);
}

TEST_F(LongNumberFixture, AssignmentOperatorCopy) {
    EAbrakhin::LongNumber original(bigNum);
    EAbrakhin::LongNumber assigned = original;
    ASSERT_EQ(bigNum, assigned);
}

TEST_F(LongNumberFixture, AssignmentOperatorMove) {
    EAbrakhin::LongNumber original(strPos);
    EAbrakhin::LongNumber originalCopy(original);
    EAbrakhin::LongNumber assigned = std::move(original);
    ASSERT_EQ(originalCopy, assigned);
}

// Comparison operators

TEST_F(LongNumberFixture, EqualityOperator) {
    EAbrakhin::LongNumber oneCopy("1");
    ASSERT_TRUE(one == oneCopy);
    ASSERT_FALSE(one == minusOne);
    ASSERT_FALSE(one == two);
}

TEST_F(LongNumberFixture, InequalityOperator) {
    ASSERT_TRUE(zero != one);
    ASSERT_TRUE(minusOne != one);
    ASSERT_FALSE(one != one);
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

TEST_F(LongNumberFixture, GreaterThanOrEqualToOperator) {
    ASSERT_TRUE(two >= one);
    ASSERT_TRUE(zero >= minusOne);
    ASSERT_FALSE(one >= two);
    ASSERT_TRUE(one >= minusOne);
}

TEST_F(LongNumberFixture, LessThanOrEqualToOperator) {
    ASSERT_TRUE(one <= two);
    ASSERT_TRUE(minusOne <= zero);
    ASSERT_FALSE(two <= one);
    ASSERT_FALSE(one <= minusOne);
}

// Arithmetic operators

TEST_F(LongNumberFixture, UnaryPlusOperator) {
    EAbrakhin::LongNumber positive = +one;
    ASSERT_EQ(one, positive);
    ASSERT_FALSE(positive.is_negative());
}

TEST_F(LongNumberFixture, UnaryMinusOperator) {
    EAbrakhin::LongNumber negated = -one;
    ASSERT_EQ(minusOne, negated);
    ASSERT_TRUE(negated.is_negative());
}

TEST_F(LongNumberFixture, AdditionOperator) {
    EAbrakhin::LongNumber sum = one + two;
    ASSERT_EQ(three, sum);
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
    EAbrakhin::LongNumber dividend(ten);
    EAbrakhin::LongNumber divisor(two);
    EAbrakhin::LongNumber quotient = dividend / divisor;
    ASSERT_EQ(five, quotient);
    ASSERT_FALSE(quotient.is_negative());
}

TEST_F(LongNumberFixture, ModulusOperator) {
    EAbrakhin::LongNumber dividend(ten);
    EAbrakhin::LongNumber divisor(three);
    EAbrakhin::LongNumber remainder = dividend % divisor;
    ASSERT_EQ(one, remainder);
    ASSERT_FALSE(remainder.is_negative());
}

// Compound arithmetic operators

TEST_F(LongNumberFixture, CompoundAdditionOperator) {
    EAbrakhin::LongNumber sum = one;
    sum += two;
    ASSERT_EQ(EAbrakhin::LongNumber(three), sum);
}

TEST_F(LongNumberFixture, CompoundSubtractionOperator) {
    EAbrakhin::LongNumber result = two;
    result -= one;
    ASSERT_EQ(one, result);
}

TEST_F(LongNumberFixture, CompoundMultiplicationOperator) {
    EAbrakhin::LongNumber product = one;
    product *= two;
    ASSERT_EQ(two, product);
}

TEST_F(LongNumberFixture, CompoundDivisionOperator) {
    EAbrakhin::LongNumber dividend(ten);
    EAbrakhin::LongNumber divisor(two);
    dividend /= divisor;
    ASSERT_EQ(five, dividend);
}

TEST_F(LongNumberFixture, CompoundModulusOperator) {
    EAbrakhin::LongNumber dividend(ten);
    EAbrakhin::LongNumber divisor(three);
    dividend %= divisor;
    ASSERT_EQ(one, dividend);
}

// Other member functions

TEST_F(LongNumberFixture, GetDigitsNumberFunction) {
    ASSERT_EQ(1, one.get_digits_number());
    ASSERT_EQ(1, zero.get_digits_number());
    ASSERT_EQ(20, bigNum.get_digits_number());
}

TEST_F(LongNumberFixture, IsNegativeFunction) {
    ASSERT_FALSE(one.is_negative());
    ASSERT_TRUE(minusOne.is_negative());
    ASSERT_FALSE(zero.is_negative());
    ASSERT_FALSE(bigNum.is_negative());
}

TEST_F(LongNumberFixture, PrintFunction) {
    testing::internal::CaptureStdout();
    one.print();
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("1", output);
}

// Friend function

TEST_F(LongNumberFixture, FriendStreamOperator) {
    testing::internal::CaptureStdout();
    std::cout << one;
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ("1", output);
}

// Tests with zero

TEST_F(LongNumberFixture, ZeroAddition) {
    EAbrakhin::LongNumber sum = zero + zero;
    ASSERT_EQ(zero, sum);
}

TEST_F(LongNumberFixture, ZeroMultiplication) {
    EAbrakhin::LongNumber product = zero * five;
    ASSERT_EQ(zero, product);
}

TEST_F(LongNumberFixture, ZeroDivision) {
    EAbrakhin::LongNumber quotient = zero / five;
    ASSERT_EQ(zero, quotient);
}

TEST_F(LongNumberFixture, ZeroModulus) {
    EAbrakhin::LongNumber remainder = zero % five;
    ASSERT_EQ(zero, remainder);
}

// Tests with negative numbers

TEST_F(LongNumberFixture, NegativeNumberOperations) {
    EAbrakhin::LongNumber negSum = one + minusOne;
    ASSERT_EQ(zero, negSum);
    ASSERT_FALSE(negSum.is_negative());

    EAbrakhin::LongNumber negProduct = two * minusOne;
    ASSERT_EQ(minusTwo, negProduct);
    ASSERT_TRUE(negProduct.is_negative());

    EAbrakhin::LongNumber negQuotient = five / minusOne;
    ASSERT_EQ(minusFive, negQuotient);
    ASSERT_TRUE(negQuotient.is_negative());

    EAbrakhin::LongNumber negRemainder = five % minusOne;
    ASSERT_EQ(zero, negRemainder);
    ASSERT_TRUE(negProduct.is_negative());
}

// Tests with large numbers

TEST_F(LongNumberFixture, LargeNumberOperations) {
    EAbrakhin::LongNumber bigSum = bigNum + one;
    ASSERT_EQ(EAbrakhin::LongNumber("12345678901234567891"), bigSum);

    EAbrakhin::LongNumber bigProduct = bigNum * two;
    ASSERT_EQ(EAbrakhin::LongNumber("24691357802469135780"), bigProduct);

    EAbrakhin::LongNumber bigQuotient = bigProduct / bigSum;
    ASSERT_EQ(one, bigQuotient);

    EAbrakhin::LongNumber bigRemainder = bigSum % bigNum;
    ASSERT_EQ(one, bigRemainder);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
