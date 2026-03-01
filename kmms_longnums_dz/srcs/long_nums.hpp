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
			//LongNumber(const int length, bool sign);
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
			
			LongNumber operator + (const LongNumber& x) ;
			LongNumber operator - (const LongNumber& x) ;
			LongNumber operator * (const LongNumber& x) const;
			LongNumber operator / (const LongNumber& x) const;
			LongNumber operator % (const LongNumber& x) const;

			bool eq_abs_comparison (const LongNumber &a, const LongNumber &b) const;
			
			friend std::ostream& operator << (std::ostream &os, const LongNumber& x);

		private:
			int get_sign(const char* const str) const noexcept;
			int get_length(const char* const str) const noexcept;
	};
}

#endif