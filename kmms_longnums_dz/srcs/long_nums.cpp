#include "long_nums.hpp"

using yenni::LongNumber;
		
LongNumber::LongNumber() { // корректный ввод по условию
	numbers = nullptr;
	length = 0;
	sign = 0;
}

LongNumber::LongNumber(int inp_length, int inp_sign) {
	length = inp_length;
	sign = inp_sign;
	if(sign == 1) {
		numbers = new int[length+1]{}; 
	}
	else 
		numbers = new int[length]{};
}

LongNumber::LongNumber(const char* const str) {
	length = get_length(str);
	sign = get_sign(str);
	numbers = new int[length - sign];
	for(int i = 0; i < length - sign; i++)
		numbers[i] = str[i+sign] - '0';
}

LongNumber::LongNumber(const LongNumber& x) {
	length = x.length;
	sign = x.sign;
	numbers = new int[length];
	for(int i = 0; i < x.length - sign; i++ ) 
		numbers[i] = x.numbers[i]; 
}

LongNumber::LongNumber(LongNumber&& x) {
	if(&x != this) {
		numbers = x.numbers;
		length = x.length;
		sign = x.sign;
		x.sign = 0;
		x.length = 0;
		x.numbers = nullptr;
	}
}

LongNumber::~LongNumber() {
	delete[] numbers;
	sign = 0;
	length = 0;
}

LongNumber& LongNumber::operator = (const char* const str) {
	length = get_length(str);
	sign = get_sign(str);
	numbers = new int[length - sign];
	for(int i = 0; i < length - sign; i++)
		numbers[i] = str[i + sign];
	return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
	length = x.length;
	sign = x.sign;
	numbers = new int[length-sign];
	for(int i = 0; i < x.length - sign; i++ ) 
		numbers[i] = x.numbers[i]; 
	return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
	if(&x != this) {
		delete[] numbers;
		numbers = x.numbers;
		length = x.length;
		sign = x.sign;
		x.numbers = nullptr;
		x.sign = 0;
		x.length = 0;
	}
	return *this;
}

bool LongNumber::operator == (const LongNumber& x) const {
	if(sign != x.sign || length != x.length)
		return false;
	else {
		for(int i = 0; i < length - sign; i++ ) {
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
	if (sign < x.sign) 
		return true;
	else if(sign > x.sign)
		return false;

	if(x.sign == 0 && sign == 0) {
		if(length > x.length)
			return true;
		else if(length == x.length) {
			return left_bigger_abs(*this, x);
		}
		else if(length < x.length)
			return false;
	}
	else if(x.sign == 1 && sign == 1)
	{
		if(length > x.length)
			return false;
		else if(length == x.length) {
			return left_bigger_abs(*this, x);
		}
		else if(length < x.length)
			return true;
	}
	return false;
}

bool LongNumber::operator < (const LongNumber& x) const {
	return !(*this > x);
}

LongNumber LongNumber::operator + (const LongNumber& x) { 
	LongNumber result;
	if (this->sign == 0 && x.sign == 0) 
		result = addition(*this, x, '+');
	else if(this->sign == 0 && x.sign == 1) {
		result = subtraction(*this, x, '+');
		if(eq_abs(*this, x)) // костыль для нулика
			result.sign = 0;
	}
	else if (this->sign == 1 && x.sign == 0) {
		result = subtraction(*this, x, '+');
		if(eq_abs(*this, x))
			result.sign = 0;
	}
	else if(this->sign == 1 && x.sign == 1)
		result = addition(*this, x, '+');

	return result;
}

LongNumber LongNumber::operator - (const LongNumber& x) { 
	LongNumber result;
	if (this->sign == 0 && x.sign == 0) {
		result = subtraction(*this, x, '-');
		if(eq_abs(*this, x))
			result.sign = 0;
	}
	else if(this->sign == 0 && x.sign == 1) { 
		result = addition(*this, x, '-');
	}
	else if (this->sign == 1 && x.sign == 0) { 
		result = addition(*this, x, '-');
		result.sign = 1;
		result.length++;
	}
	else if(this->sign == 1 && x.sign == 1) {
		result = subtraction(*this, x, '-');
		if(eq_abs(*this, x))
			result.sign = 0;
	}
	return result;
}

LongNumber LongNumber::operator * (const LongNumber& x) {
	LongNumber bigger;
	LongNumber less;
	if(this->length - this->sign > x.length - x.sign) {
		bigger = *this;
		less = x;
	}
	else if(this->length - this->sign < x.length - x.sign) {
		bigger = x;
		less = *this;
	}
	else if(this->length - this->sign == x.length - x.sign) {
		if(left_bigger_abs(*this, x)) {
			bigger = *this;
			less = x;
		}
		else {
			bigger = x;
			less = *this; 
		}
	}

	int temp_size = bigger.length - bigger.sign + less.length - less.sign;
	LongNumber result(temp_size, 0);
	add_head_zeros(bigger, temp_size);
	add_head_zeros(less, temp_size);
	
	for(int i = temp_size - 1; i >= temp_size - less.length - less.sign; i--) {
		int digit = temp_size - i - 1;
		int temp_num = 0;
		int leftover = 0;
		LongNumber interim(temp_size, 0);
		for(int j = temp_size - 1; j >= temp_size - bigger.length - bigger.sign; j--) {
			temp_num = less.numbers[i] * bigger.numbers[j];
			interim.numbers[temp_size - digit - 1] += temp_num % 10 + leftover;
			leftover = temp_num / 10;
			digit++;									
		}
		interim.numbers[temp_size - digit - 1] += leftover;
		result = result + interim;
	}
	remove_head_zeros(result);
	
	if(result.numbers[0] == 0) {
		result.sign = 0;
		result.length = 1;
	}
	else if(sign == x.sign) {
		result.sign = 0;
	}
	else if(sign != x.sign) {
		result.sign = 1;
		result.length++;
	}
	
	return result;
}

LongNumber LongNumber::operator / (const LongNumber& x) {
	LongNumber dividend = *this;
	LongNumber divider = abs_val(x);
	LongNumber result(length, 0);

	LongNumber interim("0");
	int answer_digit = 0;
	for(int i = 0; i < dividend.length - dividend.sign; i++) {
		char digit_shifting[2] = {char(dividend.numbers[i] + '0'), '\0'};
		interim = interim + LongNumber(digit_shifting);
		while(interim > divider || interim == divider) {
			answer_digit++;
			interim = interim - divider;
		}
		result.numbers[i] = answer_digit;
		answer_digit = 0;
		interim = interim * LongNumber("10");
	}

	remove_head_zeros(result);
	if(result.numbers[0] == 0) {
		result.sign = 0;
		result.length = 1;
	}
	else if(sign == x.sign) {
		result.sign = 0;
	}
	else if(sign != x.sign) {
		result.sign = 1;
		result.length++;
	}
	
	return result;
}

LongNumber LongNumber::operator % (const LongNumber& x) {
	LongNumber dividend = *this;
	LongNumber divider = abs_val(x);
	LongNumber result = dividend - ((dividend / divider) * divider);
	if(result.sign == 1) 
		result = result + divider;
	return result;
}

bool LongNumber::left_bigger_abs(const LongNumber &a, const LongNumber &b) const { 
	for(int i = 0; i < a.length-a.sign; i++) {		// true = a > b, false = a < b
		if(a.numbers[i] > b.numbers[i])
			return true;
		else if (a.numbers[i] < b.numbers[i])
			return false;
	}
	return false;
}

bool LongNumber::eq_abs(const LongNumber &a, const LongNumber &b) const {
	if(a.length - a.sign == b.length - b.sign) {
		for(int i = 0; i < a.length - a.sign; i++) {
			if(a.numbers[i] != b.numbers[i])
				return false;
		}
	}
	else 
		return false;

	return true;
}

LongNumber LongNumber::abs_val(const LongNumber &inp) const {
	LongNumber result = inp;
	if(inp.sign == 1) {
		result.sign = 0;
		result.length--;
	}
	return result;
}

LongNumber LongNumber::addition(const LongNumber &a, const LongNumber &b, char &&mother_func) {
	LongNumber bigger;
	LongNumber less;
	LongNumber result;
    if(a.length - a.sign > b.length - b.sign) {
		bigger = a;
		less = b;
	}
	else if(a.length - a.sign < b.length - b.sign) {
		bigger = b;
		less = a;
	}
	else if(a.length - a.sign == b.length - b.sign) {
		if(left_bigger_abs(a, b)) {
			bigger = a;
			less = b;
		}
		else {
			bigger = b;
			less = a;
		}
	}

    int temp_size = bigger.length + 1 - bigger.sign;

    int *res_nums = new int[temp_size]{};
	add_head_zeros(bigger, temp_size);
	add_head_zeros(less, temp_size);

    for(int i = temp_size-1; i >= 0; i--) {
        if(bigger.numbers[i] + less.numbers[i] < 10) 
            res_nums[i] += bigger.numbers[i] + less.numbers[i];
        else if(bigger.numbers[i] + less.numbers[i] >= 10) {
            res_nums[i] += (bigger.numbers[i] + less.numbers[i]) % 10;
            bigger.numbers[i-1] += 1;
        } 
    }
	result.numbers = res_nums ;
    result.length = bigger.length + 1 - bigger.sign; 
	
	if(mother_func == '+') 
		result.sign = bigger.sign;
	else if(mother_func == '-') {
		result.sign = less.sign;
	}

    res_nums = nullptr; 
    bigger.numbers = nullptr;
    less.numbers = nullptr;

	remove_head_zeros(result);
    return result;
}

LongNumber LongNumber::subtraction (const LongNumber &a, const LongNumber &b, char &&mother_func ) {
	LongNumber bigger;
	LongNumber less;
	LongNumber result;
	if(a.length - a.sign > b.length - b.sign) { 
		bigger = a;
		less = b;
	}
	else if(a.length - a.sign < b.length - b.sign) {
		bigger = b;
		less = a;
	}
	else if(a.length - a.sign == b.length - b.sign) {
		if(left_bigger_abs(a, b)) {
			bigger = a;
			less = b;
		}
		else {
			bigger = b;
			less = a;
		}
	}

	int temp_size = bigger.length - bigger.sign;
	int *res_nums = new int[temp_size]{};
	add_head_zeros(less, temp_size);

	for(int i = temp_size-1; i >= 0; i--) { 
		if(bigger.numbers[i] - less.numbers[i] >= 0) {
			res_nums[i] += bigger.numbers[i] - less.numbers[i];
		}
		else if(bigger.numbers[i] - less.numbers[i] < 0) {
			bigger.numbers[i-1] -= 1;
			bigger.numbers[i] += 10;
			res_nums[i] += bigger.numbers[i] - less.numbers[i];
		} 
	}
	result.numbers = res_nums;
    result.length = temp_size;
	if(mother_func == '+') {
		result.sign = bigger.sign;
		result.length += bigger.sign;
	}
	else if(mother_func == '-') {
		if(a == b)
			result.sign = 0;
		else if(a > b)
			result.sign = 0;
		else if(a < b) {
			result.sign = 1;
			result.length++;
		}
	}
	res_nums = nullptr; 
    bigger.numbers = nullptr;
    less.numbers = nullptr;

	remove_head_zeros(result);
	return result;
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

void LongNumber::add_head_zeros(LongNumber &x, int size) {
	int *new_size = new int[size]{};
	for(int i = x.length-1-x.sign; i >= 0; i--) {
		new_size[i+size-x.length+x.sign] = x.numbers[i];
	}
	delete[] x.numbers;
	x.numbers = new_size;
}

void LongNumber::remove_head_zeros(LongNumber &x) {
	int head_zeros = 0; 
	int to_zero_counter = x.length;
	while(x.numbers[head_zeros] == 0 && to_zero_counter != 1) {
		head_zeros++;
		to_zero_counter--;
	}
	if(head_zeros == 0)
		return;

	int new_size = x.length - head_zeros;
	int *new_numbers = new int[new_size];

	for(int i = 0; i < new_size; i++) {
		new_numbers[i] = x.numbers[i + head_zeros-x.sign];
	}
	delete[] x.numbers;
	x.length = new_size;
	x.numbers = new_numbers;
	return;
}
// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace yenni {
	std::ostream& operator << (std::ostream &os, const LongNumber& x) {
		if(x.sign == 1) os << "-";
		for(int i = 0; i < x.length - x.sign; i++) {
			os << x.numbers[i];
		}
		return os;
	}
}