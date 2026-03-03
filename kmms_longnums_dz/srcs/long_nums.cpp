#include "long_nums.hpp"

using yenni::LongNumber;
		
			/*int* numbers;
			int length;
			bool sign;*/
LongNumber::LongNumber() { // корректный ввод по условию
	numbers = nullptr;
	length = 0;
	sign = 0;
}
/*
LongNumber::LongNumber(int inp_length, bool inp_sign) {
	length = inp_length;
	sign = inp_sign;
	if(!sign) {
		numbers = new int[length+1]; 
	}
	else 
		numbers = new int[length];
}*/

LongNumber::LongNumber(const char* const str) {
	length = get_length(str);
	sign = get_sign(str);
	numbers = new int[length];
	for(int i = sign; i < length; i++)
		numbers[i] = str[i] - '0';
}

LongNumber::LongNumber(const LongNumber& x) {
	length = x.length;
	sign = x.sign;
	numbers = new int[length];
	for(int i = x.sign; i < x.length; i++ ) 
		numbers[i] = x.numbers[i]; 
}

LongNumber::LongNumber(LongNumber&& x) {
	if(&x != this) {
		length = x.length;
		sign = x.sign;
		numbers = new int[length];
		numbers = x.numbers;
		x = nullptr;
	}
}

LongNumber::~LongNumber() {
	delete[] numbers;
}

LongNumber& LongNumber::operator = (const char* const str) {
	length = get_length(str);
	sign = get_sign(str);
	numbers = new int[length];
	for(int i = sign; i < length; i++)
		numbers[i] = str[i];
	return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
	length = x.length;
	sign = x.sign;
	numbers = new int[length];
	for(int i = x.sign; i < x.length; i++ ) 
		numbers[i] = x.numbers[i]; 
	return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
	if(&x != this) {
		delete[] numbers;
		length = x.length;
		sign = x.sign;
		numbers = x.numbers; 
		x = nullptr;
		return *this;
	}
}

bool LongNumber::operator == (const LongNumber& x) const {
	if(sign != x.sign || length != x.length)
		return false;
	else {
		for(int i = 0; i < length; i++ ) {
			if (numbers[i] != x.numbers[i])
				return false;
		}
		return true;
	}
}

bool LongNumber::operator != (const LongNumber& x) const {
	return !(*this == x);
}

bool LongNumber::operator > (const LongNumber& x) const { // '-' = 1, '+' = '' = 0
	if (sign < x.sign) // 52 | 25
		return true;
	else if(sign > x.sign)
		return false;
	else if(x.sign == 0 && sign == 0) {
		if(length > x.length)
			return true;
		else if(length == x.length) {
			return eq_abs_comparison(*this, x);
		}
		else if(length < x.length)
			return false;
	}
	else if(sign == x.sign && sign == 1)
	{
		if(length > x.length)
			return false;
		else if(length == x.length) {
			return eq_abs_comparison(*this, x);
		}
		else if(length < x.length)
			return true;
	}
}

bool LongNumber::operator < (const LongNumber& x) const {
	return !(*this > x);
}

LongNumber LongNumber::operator + (const LongNumber& x) const { //6718 + 381
	LongNumber bigger;
	LongNumber less;
	LongNumber result;
    if(length >= x.length) {
        bigger = *this;
        less = x;
    }
    else if(length <= x.length) {
        bigger = x;
        less = *this;
    }

    int temp_size = bigger.length + 1;

    int *res_nums = new int[temp_size]{};

    for(int i = bigger.length-1; i >= 0; i--) {
        if(bigger.numbers[i] + less.numbers[i] < 10) 
            res_nums[i+1] += bigger.numbers[i] + less.numbers[i];
        else if(bigger.numbers[i] + less.numbers[i] >= 10) {
            res_nums[i+1] += (bigger.numbers[i] + less.numbers[i]) % 10;
            bigger.numbers[i-1] += 1;
        } 
    }
    if(res_nums[0] == 0) {
        result.numbers = res_nums + 1;
        result.length = bigger.length; 
    } 
    else if(res_nums[0] != 0) {
        result.numbers = res_nums;
        result.length = bigger.length + 1;
    }
    res_nums = nullptr; // mem leakage
    bigger.numbers = nullptr;
    less.numbers = nullptr;

    return result;
}

LongNumber LongNumber::operator - (const LongNumber& x) const { //6718 + 981
	LongNumber bigger;
	LongNumber less;
	LongNumber result;
	if(length >= x.length) {
		bigger = *this;
		less = x;
	}
	else if(length <= x.length) {
		bigger = x;
		less = *this;
	}

	int temp_size = bigger.length + 2;
	int *res_nums = new int[temp_size]{};

	for(int i = bigger.length-1; i >= 0; i--) {
		if(bigger.numbers[i] - less.numbers[i] >= 0) 
			res_nums[i] += bigger.numbers[i] - less.numbers[i];
		else if(bigger.numbers[i] - less.numbers[i] < 0) {
			bigger.numbers[i-1] -= 1;
			bigger.numbers[i] += 10;
			res_nums[i] += bigger.numbers[i] - less.numbers[i];
		} 
	}

	int head_zeros = 0;
	for(int i = 0; i < temp_size; i++) {
		if(res_nums[i] == 0 && res_nums[i+1] == 0)
			head_zeros++;
		else 
			break;
	}

	result.numbers = res_nums + head_zeros;
	res_nums = nullptr;

	return result;
}

LongNumber LongNumber::operator * (const LongNumber& x) const {
	// TODO
}

LongNumber LongNumber::operator / (const LongNumber& x) const {
	// TODO
}

LongNumber LongNumber::operator % (const LongNumber& x) const {
	// TODO
}

bool LongNumber::eq_abs_comparison(const LongNumber &a, const LongNumber &b) const { 
	for(int i = 0; i < a.length; i++) {		// true = a > b, false = a < b
		if(a.numbers[i] > b.numbers[i])
			return true;
	}
	return false;
}

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
int LongNumber::get_length(const char* const str) const noexcept {
	int length = 0;
	while(str[length] != '\0') {
		length++;
	}
	return length;
}

int LongNumber::get_sign(const char* const str) const noexcept {
	if(str[0] == '-')
		return 1;
	else
		return 0;
}

// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace yenni {
	std::ostream& operator << (std::ostream &os, const LongNumber& x) {
		if(x.sign == 1) os << "-";
		for(int i = 0; i < x.length; i++) {
			os << x.numbers[i];
		}
		return os;
	}
	
}

int main() {
	LongNumber result = LongNumber("23") + LongNumber("17");
	std::cout << result;
}