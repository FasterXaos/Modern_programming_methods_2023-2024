#pragma once

#include <iostream>

namespace EAbrakhin {
	class LongNumber {
		static const char MINUS = '-';
		static const char STR_ZERO = '0';

		int* numbers;
		int length;
		int isNegative;

	public:
		LongNumber();
		LongNumber(long long value);
		LongNumber(const char* const str);
		LongNumber(const LongNumber& x);
		LongNumber(LongNumber&& x);

		~LongNumber();

		LongNumber& operator = (long long value);
		LongNumber& operator = (const char* const str);
		LongNumber& operator = (const LongNumber& x);
		LongNumber& operator = (LongNumber&& x);

		bool operator == (const LongNumber& x) const;
		bool operator != (const LongNumber& x) const;
		bool operator > (const LongNumber& x) const;
		bool operator < (const LongNumber& x) const;
		bool operator >= (const LongNumber& x) const;
		bool operator <= (const LongNumber& x) const;

		LongNumber operator + () const;
		LongNumber operator - () const;

		LongNumber operator + (const LongNumber& x) const;
		LongNumber operator - (const LongNumber& x) const;
		LongNumber operator * (const LongNumber& x) const;
		LongNumber operator / (const LongNumber& x) const;
		LongNumber operator % (const LongNumber& x) const;

		LongNumber& operator += (const LongNumber& x);
		LongNumber& operator -= (const LongNumber& x);
		LongNumber& operator *= (const LongNumber& x);
		LongNumber& operator /= (const LongNumber& x);
		LongNumber& operator %= (const LongNumber& x);

		int get_digits_number() const;
		bool is_negative() const;
		void print();

		friend std::ostream& operator << (std::ostream& os, const LongNumber& x);
	};
}
