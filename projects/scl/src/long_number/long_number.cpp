#include "long_number.hpp"

namespace EAbrakhin {
	LongNumber::LongNumber() :
		numbers(new int[1]),
		length(1), 
		isNegative(0)
	{
		numbers[0] = 0;
	}

	LongNumber::LongNumber(const char* const str) : 
		length(get_lenght(str)), 
		isNegative(0)
	{
		int start_index = 0;
		if (str[0] == MINUS) {
			isNegative = 1;
			start_index = 1;
			--length;
		}

		numbers = new int[length];
		for (int i = start_index; i < length + isNegative; ++i) {
			numbers[i - start_index] = str[i] - STR_ZERO;
		}
	}

	LongNumber::LongNumber(long long value) {
		if (value < 0) {
			isNegative = 1;
			value = -value;
		} else
			isNegative = 0;

		long long temp = value;
		length = 0;
		while (temp > 0) {
			temp /= 10;
			++length;
		}

		numbers = new int[length];

		for (int i = length - 1; i >= 0; --i) {
			numbers[i] = value % 10;
			value /= 10;
		}
	}

	LongNumber::LongNumber(const LongNumber& x) : 
		numbers(new int[x.length]),
		length(x.length), 
		isNegative(x.isNegative)
	{
		for (int i = 0; i < length; ++i) {
			numbers[i] = x.numbers[i];
		}
	}
	
	LongNumber::LongNumber(LongNumber&& x): 
		numbers(x.numbers), 
		length(x.length), 
		isNegative(x.isNegative)
	{
		x.numbers = new int[1];
		x.numbers[0] = 0;
		x.length = 1;
		x.isNegative = 0;
	}
	
	LongNumber::~LongNumber() {
		delete[] numbers;
	}

	
	LongNumber& LongNumber::operator = (const char* const str) {
		delete[] numbers;
		isNegative = 0;

		length = get_lenght(str);

		int start_index = 0;
		if (str[0] == MINUS) {
			isNegative = 1;
			start_index = 1;
			--length;
		} else
			isNegative = 0;

		numbers = new int[length];
		for (int i = start_index; i < length + isNegative; ++i) {
			numbers[i - start_index] = str[i] - STR_ZERO;
		}

		return *this;
	}

	LongNumber& LongNumber::operator = (long long value) {
		if (value < 0) {
			isNegative = 1;
			value = -value;
		} else
			isNegative = 0;

		long long temp = value;
		length = 0;
		while (temp > 0) {
			temp /= 10;
			++length;
		}

		delete[] numbers;
		numbers = new int[length];
		for (int i = length - 1; i >= 0; --i) {
			numbers[i] = value % 10;
			value /= 10;
		}

		return *this;
	}
	
	LongNumber& LongNumber::operator = (const LongNumber& x) {
		if (this != &x) {
			delete[] numbers;
			length = x.length;
			isNegative = x.isNegative;

			numbers = new int[length];
			for (int i = 0; i < length; ++i) {
				numbers[i] = x.numbers[i];
			}
		}

		return *this;
	}
	
	LongNumber& LongNumber::operator = (LongNumber&& x) {
		if (this != &x) {
			delete[] numbers;
			length = x.length;
			isNegative = x.isNegative;
			numbers = x.numbers;

			x.numbers = new int[1];
			x.numbers[0] = 0;
			x.length = 1;
			x.isNegative = 0;
		}

		return *this;
	}
	

	bool LongNumber::operator == (const LongNumber& x) const {
		if (length != x.length || isNegative != x.isNegative) {
			return false;
		}

		for (int i = 0; i < length; ++i) {
			if (numbers[i] != x.numbers[i]) {
				return false;
			}
		}

		return true;
	}

	bool LongNumber::operator != (const LongNumber& x) const {
		return !(*this == x);
	}
	
	bool LongNumber::operator > (const LongNumber& x) const {
		if (isNegative != x.isNegative) {
			return !isNegative;
		}

		if (length != x.length) {
			return (length > x.length) == !isNegative;
		}

		for (int i = 0; i < length; ++i) {
			if (numbers[i] != x.numbers[i]) {
				return (numbers[i] > x.numbers[i]) == !isNegative;
			}
		}

		return false;
	}
	
	bool LongNumber::operator < (const LongNumber& x) const {
		return !(*this > x) && !(*this == x);
	}

	bool LongNumber::operator >= (const LongNumber& x) const {
		return (*this > x) || (*this == x);
	}

	bool LongNumber::operator <= (const LongNumber& x) const {
		return (*this < x) || (*this == x);
	}


	LongNumber LongNumber::operator+() const {
		return *this;
	}

	LongNumber LongNumber::operator-() const {
		LongNumber negated(*this);
		negated.isNegative = (isNegative ? 0 : 1);
		
		return negated;
	}

	
	LongNumber LongNumber::operator + (const LongNumber& x) const {
		if (isNegative != x.isNegative)
			return isNegative ? (x - (-LongNumber(*this))) : (*this - (-LongNumber(x)));
		else {
			LongNumber result;
			int carry = 0;
			int max_length = (length > x.length) ? length : x.length;

			result.length = max_length + 1;
			delete result.numbers;
			result.numbers = new int[result.length];

			int i = length - 1;
			int j = x.length - 1;
			int k = result.length - 1;

			while (i >= 0 || j >= 0) {
				int sum = carry;
				if (i >= 0)
					sum += numbers[i--];
				if (j >= 0)
					sum += x.numbers[j--];
				result.numbers[k--] = sum % 10;
				carry = sum / 10;
			}
			result.numbers[k--] = carry;

			result.isNegative = isNegative;

			int index = 0;
			while (index < result.length && result.numbers[index] == 0) {
				++index;
			}
			if (index == result.length) {
				result.length = 1;
				delete[] result.numbers;
				result.numbers = new int[1];
				result.numbers[0] = 0;
			} else {
				result.length -= index;
				int* temp = new int[result.length];
				for (int i = 0; i < result.length; ++i) {
					temp[i] = result.numbers[index + i];
				}
				delete[] result.numbers;
				result.numbers = temp;
			}

			return result;
		}
	}
	
	LongNumber LongNumber::operator - (const LongNumber& x) const {
		if (*this == x)
			return LongNumber();

		if (!(!isNegative && !x.isNegative))
			return isNegative && x.isNegative ? ((-LongNumber(x)) - (-LongNumber(*this))) : (*this + (-LongNumber(x)));

		LongNumber result;
		if (*this < x) {
			result = (LongNumber(x) - LongNumber(*this));
			result.isNegative = 1;
			return result;
		}

		int borrow = 0;
		int max_length = (length > x.length) ? length : x.length;

		result.length = max_length;
		delete[] result.numbers;
		result.numbers = new int[result.length];

		int i = length - 1;
		int j = x.length - 1;
		int k = result.length - 1;

		while (i >= 0 || j >= 0) {
			int diff = borrow;
			if (i >= 0)
				diff += numbers[i--];
			if (j >= 0)
				diff -= x.numbers[j--];
			if (diff < 0) {
				diff += 10;
				borrow = -1;
			} else {
				borrow = 0;
			}
			result.numbers[k--] = diff;
		}

		int index = 0;
		while (index < result.length && result.numbers[index] == 0) {
			++index;
		}
		if (index == result.length) {
			result.length = 1;
			delete[] result.numbers;
			result.numbers = new int[1];
			result.numbers[0] = 0;
		} else {
			result.length -= index;
			int* temp = new int[result.length];
			for (int i = 0; i < result.length; ++i) {
				temp[i] = result.numbers[index + i];
			}
			delete[] result.numbers;
			result.numbers = temp;
		}

		return result;
	}
	
	LongNumber LongNumber::operator * (const LongNumber& x) const {
		if (*this == LongNumber("0") || x == LongNumber("0"))
			return LongNumber("0");

		int resultSize = length + x.length;
		int* resultDigits = new int[resultSize];

		for (int i = 0; i < resultSize; ++i) {
			resultDigits[i] = 0;
		}

		for (int i = length - 1; i >= 0; --i) {
			int carry = 0;
			for (int j = x.length - 1; j >= 0; --j) {
				int product = numbers[i] * x.numbers[j] + resultDigits[i + j + 1] + carry;
				resultDigits[i + j + 1] = product % 10;
				carry = product / 10;
			}
			resultDigits[i] += carry;
		}

		int startIndex = 0;
		while (startIndex < resultSize && resultDigits[startIndex] == 0) {
			++startIndex;
		}

		LongNumber result;
		result.length = resultSize - startIndex;
		result.numbers = new int[result.length];
		for (int i = 0; i < result.length; ++i) {
			result.numbers[i] = resultDigits[startIndex + i];
		}
		result.isNegative = isNegative != x.isNegative;

		delete[] resultDigits;

		return result;
	}
	
	LongNumber LongNumber::operator / (const LongNumber& x) const {
		if (x == LongNumber("0")) {
			throw std::runtime_error("division by zero");
		}

		if (*this == LongNumber("0"))
			return LongNumber("0");

		if (x == LongNumber("1") || x == LongNumber("-1")) {
			if (isNegative == x.isNegative)
				return LongNumber(*this);
			else
				return LongNumber(isNegative ? *this : -LongNumber(*this));
		}

		LongNumber result;
		LongNumber dividend(*this);
		LongNumber divisor(x);
		dividend.isNegative = 0;
		divisor.isNegative = 0;

		while (dividend >= divisor) {
			dividend = dividend - divisor;
			result += LongNumber("1");
		}

		result.isNegative = (isNegative != x.isNegative);

		return result;
	}
	
	LongNumber LongNumber::operator % (const LongNumber& x) const {
		if (x == LongNumber("0"))
			throw std::runtime_error("division by zero");

		if (x == LongNumber("1") || x == LongNumber("-1"))
			return LongNumber("0");

		LongNumber dividend(*this);
		LongNumber divisor(x);
		dividend.isNegative = 0;
		divisor.isNegative = 0;

		while (dividend >= divisor) {
			dividend = dividend - divisor;
		}

		dividend.isNegative = isNegative;

		return dividend;
	}


	LongNumber& LongNumber::operator += (const LongNumber& x) {
		*this = *this + x;
		return *this;
	}

	LongNumber& LongNumber::operator -= (const LongNumber& x) {
		*this = *this - x;
		return *this;
	}

	LongNumber& LongNumber::operator *= (const LongNumber& x) {
		*this = *this * x;
		return *this;
	}

	LongNumber& LongNumber::operator /= (const LongNumber& x) {
		*this = *this / x;
		return *this;
	}

	LongNumber& LongNumber::operator %= (const LongNumber& x) {
		*this = *this % x;
		return *this;
	}

	
	int LongNumber::get_digits_number() const {
		return length;
	}
	
	bool LongNumber::is_negative() const {
		return isNegative;
	}

	void LongNumber::print() const{
		if (isNegative)
			std::cout << MINUS;

		for (int i = 0; i < length; ++i)
			std::cout << numbers[i];
	}
	

	std::ostream& operator << (std::ostream &os, const LongNumber& x) {
		if (x.isNegative)
			os << '-';

		for (int i = 0; i < x.length; ++i) {
			os << x.numbers[i];
		}

		return os;
	}

	int LongNumber::get_lenght(const char* const str) const {
		const char* s = str;
		while (*s) {
			++s;
		}

		return (s - str);
	}
}
