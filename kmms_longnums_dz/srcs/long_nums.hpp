#ifndef LONG_NUMS_HPP
#define LONG_NUMS_HPP

#include <iostream>

namespace yenni {
	class LongNumber {
		private:
			int* numbers;
			int length;
			int sign;
		public:
		
		public:
			LongNumber();
			LongNumber(int length, int sign);
			LongNumber(const char* const str);
			LongNumber(const LongNumber& x);
			LongNumber(LongNumber&& x);
			
			~LongNumber();
			
			LongNumber& operator = (const char* const str);
			LongNumber& operator = (const LongNumber& x);
			LongNumber& operator = (LongNumber&& x);
			
			bool operator == (const LongNumber& x) const;
			bool operator != (const LongNumber& x) const;
			bool operator > (const LongNumber& x) const;
			bool operator < (const LongNumber& x) const;
			
			LongNumber operator + (const LongNumber& x);
			LongNumber operator - (const LongNumber& x);
			LongNumber operator * (const LongNumber& x);
			LongNumber operator / (const LongNumber& x);
			LongNumber operator % (const LongNumber& x);

			bool left_bigger_abs (const LongNumber &a, const LongNumber &b) const;
			bool eq_abs (const LongNumber &a, const LongNumber &b) const;
			LongNumber addition (const LongNumber &a, const LongNumber &b, char &&mother_func);
			LongNumber subtraction (const LongNumber &a, const LongNumber &b, char &&mother_func);
			LongNumber multiply_one_digit(const LongNumber &inp, int digit);
			
			friend std::ostream& operator << (std::ostream &os, const LongNumber& x);

		private:
			void add_head_zeros(LongNumber &x, int size);
			void remove_head_zeros(LongNumber &x);
			int get_sign(const char* const str) const noexcept;
			int get_length(const char* const str) const noexcept;
	};
}

#endif