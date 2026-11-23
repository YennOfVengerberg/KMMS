#include "long_nums.hpp"

#include <algorithm>
#include <stdexcept>
#include <utility>

using yenni::LongNumber;

// ============================================================================
// 1. КОНСТРУКТОРЫ, ДЕСТРУКТОР И ОПЕРАТОРЫ ПРИСВАИВАНИЯ (Rule of Five)
// ============================================================================

LongNumber::LongNumber() : numbers(nullptr), length(0), sign(0) {}

LongNumber::LongNumber(int inp_length, int inp_sign) {
	if (inp_length <= 0) {
		numbers = nullptr;
		length = 0;
		sign = 0;
		return;
	}
	sign = (inp_sign == 1) ? 1 : 0;
	numbers = new int[inp_length]{};
	length = inp_length + sign;
}

LongNumber::LongNumber(int num) {
	if (num == 0) {
		sign = 0;
		length = 1;
		numbers = new int[1]{0};
		return;
	}

	sign = (num < 0) ? 1 : 0;
	std::uint64_t abs_num = (num < 0)
		? static_cast<std::uint64_t>(-(static_cast<std::int64_t>(num)))
		: static_cast<std::uint64_t>(num);

	int digits = 0;
	std::uint64_t copy = abs_num;
	while (copy > 0) {
		digits++;
		copy /= 10;
	}

	length = digits + sign;
	numbers = new int[digits]{};
	for (int i = digits - 1; i >= 0; i--) {
		numbers[i] = static_cast<int>(abs_num % 10);
		abs_num /= 10;
	}
}

LongNumber::LongNumber(const char* const str) : numbers(nullptr), length(0), sign(0) {
	*this = str;
}

LongNumber::LongNumber(const LongNumber& x) {
	if (x.numbers == nullptr || x.length == 0) {
		numbers = nullptr;
		length = 0;
		sign = 0;
		return;
	}
	length = x.length;
	sign = x.sign;
	const int digits = x.digits_count();
	numbers = new int[digits]{};
	for (int i = 0; i < digits; i++) {
		numbers[i] = x.numbers[i];
	}
}

LongNumber::LongNumber(LongNumber&& x) noexcept
	: numbers(x.numbers), length(x.length), sign(x.sign) {
	x.numbers = nullptr;
	x.length = 0;
	x.sign = 0;
}

LongNumber::~LongNumber() {
	delete[] numbers;
	numbers = nullptr;
	length = 0;
	sign = 0;
}

LongNumber& LongNumber::operator = (const char* const str) {
	if (str == nullptr || str[0] == '\0') {
		delete[] numbers;
		numbers = nullptr;
		length = 0;
		sign = 0;
		return *this;
	}

	const int raw_len = get_length(str);
	const int raw_sign = get_sign(str);

	int first_non_zero = raw_sign;
	while (first_non_zero < raw_len - 1 && str[first_non_zero] == '0') {
		first_non_zero++;
	}

	const int digits = raw_len - first_non_zero;
	const bool zero_value = (digits == 1 && str[first_non_zero] == '0');

	int* new_numbers = new int[digits]{};
	for (int i = 0; i < digits; i++) {
		new_numbers[i] = str[first_non_zero + i] - '0';
	}

	delete[] numbers;
	numbers = new_numbers;
	sign = zero_value ? 0 : raw_sign;
	length = digits + sign;
	return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
	if (this == &x) {
		return *this;
	}
	if (x.numbers == nullptr || x.length == 0) {
		delete[] numbers;
		numbers = nullptr;
		length = 0;
		sign = 0;
		return *this;
	}

	const int digits = x.digits_count();
	int* new_numbers = new int[digits]{};
	for (int i = 0; i < digits; i++) {
		new_numbers[i] = x.numbers[i];
	}

	delete[] numbers;
	numbers = new_numbers;
	length = x.length;
	sign = x.sign;
	return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) noexcept {
	if (this != &x) {
		delete[] numbers;
		numbers = x.numbers;
		length = x.length;
		sign = x.sign;
		x.numbers = nullptr;
		x.length = 0;
		x.sign = 0;
	}
	return *this;
}

// ============================================================================
// 2. ОПЕРАТОРЫ СРАВНЕНИЯ
// ============================================================================

bool LongNumber::operator == (const LongNumber& x) const {
	if (is_zero() && x.is_zero()) {
		return true;
	}
	if (sign != x.sign || length != x.length) {
		return false;
	}
	const int digits = digits_count();
	for (int i = 0; i < digits; i++) {
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
	if (*this == x) {
		return false;
	}
	if (sign != x.sign) {
		return sign < x.sign;
	}
	const bool abs_greater = left_bigger_abs(*this, x);
	return (sign == 0) ? abs_greater : !abs_greater;
}

bool LongNumber::operator < (const LongNumber& x) const {
	return x > *this;
}

// ============================================================================
// 3. АРИФМЕТИЧЕСКИЕ ОПЕРАТОРЫ (+, -, *, /, %)
// ============================================================================

LongNumber LongNumber::operator + (const LongNumber& x) const {
	const std::vector<int> a = to_poly_digits();
	const std::vector<int> xb = x.to_poly_digits();

	if (sign == x.sign) {
		return from_poly_digits(add_poly(a, xb), sign);
	}

	const int cmp = compare_abs(a, xb);
	if (cmp == 0) {
		return LongNumber(0);
	}
	if (cmp > 0) {
		return from_poly_digits(sub_poly(a, xb), sign);
	}
	return from_poly_digits(sub_poly(xb, a), x.sign);
}

LongNumber LongNumber::operator - (const LongNumber& x) const {
	LongNumber neg_x = x;
	if (!neg_x.is_zero()) {
		if (neg_x.sign == 0) {
			neg_x.sign = 1;
			neg_x.length++;
		} else {
			neg_x.sign = 0;
			neg_x.length--;
		}
	}
	return (*this) + neg_x;
}

LongNumber LongNumber::operator * (const LongNumber& x) const {
	if (is_zero() || x.is_zero()) {
		return LongNumber(0);
	}
	const std::vector<int> a = to_poly_digits();
	const std::vector<int> b = x.to_poly_digits();
	const std::vector<int> prod = multiply_poly(a, b);
	const int res_sign = (sign == x.sign) ? 0 : 1;
	return from_poly_digits(prod, res_sign);
}

LongNumber LongNumber::operator / (const LongNumber& x) const {
	if (x.is_zero()) {
		throw std::domain_error("Division by zero in LongNumber::operator/");
	}
	if (is_zero()) {
		return LongNumber(0);
	}

	const std::vector<int> u = to_poly_digits();
	const std::vector<int> v = x.to_poly_digits();

	auto [q_poly, r_poly] = divmod_poly(u, v);

	// Евклидово деление (0 <= r < |b|): при отрицательном делимом и ненулевом остатке
	// модуль частного увеличивается на 1 (например, -100 / 6 = -17, остаток 2).
	const bool has_remainder = !(r_poly.size() == 1 && r_poly[0] == 0);
	if (this->sign == 1 && has_remainder) {
		q_poly = add_poly(q_poly, {1});
	}

	const int res_sign = (this->sign == x.sign) ? 0 : 1;
	return from_poly_digits(q_poly, res_sign);
}

LongNumber LongNumber::operator % (const LongNumber& x) const {
	if (x.is_zero()) {
		throw std::domain_error("Modulo by zero in LongNumber::operator%");
	}
	if (is_zero()) {
		return LongNumber(0);
	}

	const std::vector<int> u = to_poly_digits();
	const std::vector<int> v = x.to_poly_digits();

	auto [q_poly, r_poly] = divmod_poly(u, v);
	(void)q_poly;

	const bool has_remainder = !(r_poly.size() == 1 && r_poly[0] == 0);
	if (this->sign == 1 && has_remainder) {
		r_poly = sub_poly(v, r_poly);
	}
	return from_poly_digits(r_poly, 0);
}

// ============================================================================
// 4. БАЗОВЫЕ ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ И ПРЕДСТАВЛЕНИЕ МНОГОЧЛЕНОВ
// ============================================================================

int LongNumber::digits_count() const noexcept {
	return (numbers == nullptr || length <= sign) ? 0 : (length - sign);
}

bool LongNumber::is_zero() const noexcept {
	const int digits = digits_count();
	if (digits == 0) {
		return true;
	}
	for (int i = 0; i < digits; i++) {
		if (numbers[i] != 0) {
			return false;
		}
	}
	return true;
}

int LongNumber::compare_abs(const std::vector<int>& a, const std::vector<int>& b) noexcept {
	if (a.size() != b.size()) {
		return (a.size() > b.size()) ? 1 : -1;
	}
	for (int i = static_cast<int>(a.size()) - 1; i >= 0; i--) {
		if (a[i] != b[i]) {
			return (a[i] > b[i]) ? 1 : -1;
		}
	}
	return 0;
}

bool LongNumber::left_bigger_abs(const LongNumber& a, const LongNumber& b) const {
	const int da = a.digits_count();
	const int db = b.digits_count();
	if (da != db) {
		return da > db;
	}
	for (int i = 0; i < da; i++) {
		if (a.numbers[i] != b.numbers[i]) {
			return a.numbers[i] > b.numbers[i];
		}
	}
	return false;
}

bool LongNumber::eq_abs(const LongNumber& a, const LongNumber& b) const {
	const int da = a.digits_count();
	const int db = b.digits_count();
	if (da != db) {
		return false;
	}
	for (int i = 0; i < da; i++) {
		if (a.numbers[i] != b.numbers[i]) {
			return false;
		}
	}
	return true;
}

LongNumber LongNumber::abs_val(const LongNumber& inp) const {
	LongNumber result = inp;
	if (inp.sign == 1) {
		result.sign = 0;
		result.length--;
	}
	return result;
}

int LongNumber::get_length(const char* const str) const noexcept {
	int len = 0;
	while (str[len] != '\0') {
		len++;
	}
	return len;
}

int LongNumber::get_sign(const char* const str) const noexcept {
	return (str[0] == '-') ? 1 : 0;
}

std::vector<int> LongNumber::to_poly_digits() const {
	const int digits = digits_count();
	if (digits == 0) {
		return {0};
	}
	std::vector<int> poly(digits);
	for (int i = 0; i < digits; i++) {
		poly[i] = numbers[digits - 1 - i];
	}
	trim_poly(poly);
	return poly;
}

LongNumber LongNumber::from_poly_digits(const std::vector<int>& poly_in, int result_sign) {
	std::vector<int> poly = poly_in;
	trim_poly(poly);

	if (poly.size() == 1 && poly[0] == 0) {
		return LongNumber(0);
	}

	const int digits = static_cast<int>(poly.size());
	const int clean_sign = (result_sign == 1) ? 1 : 0;
	LongNumber res(digits, clean_sign);
	for (int i = 0; i < digits; i++) {
		res.numbers[i] = poly[digits - 1 - i];
	}
	return res;
}

void LongNumber::trim_poly(std::vector<int>& poly) {
	while (poly.size() > 1 && poly.back() == 0) {
		poly.pop_back();
	}
	if (poly.empty()) {
		poly.push_back(0);
	}
}

std::vector<int> LongNumber::add_poly(const std::vector<int>& a, const std::vector<int>& b) {
	const std::size_t n = std::max(a.size(), b.size());
	std::vector<int> res;
	res.reserve(n + 1);

	int carry = 0;
	for (std::size_t i = 0; i < n || carry > 0; i++) {
		int sum = carry;
		if (i < a.size()) sum += a[i];
		if (i < b.size()) sum += b[i];
		res.push_back(sum % 10);
		carry = sum / 10;
	}
	trim_poly(res);
	return res;
}

std::vector<int> LongNumber::sub_poly(const std::vector<int>& a, const std::vector<int>& b) {
	std::vector<int> res(a.size(), 0);
	int borrow = 0;
	for (std::size_t i = 0; i < a.size(); i++) {
		int diff = a[i] - borrow - (i < b.size() ? b[i] : 0);
		if (diff < 0) {
			diff += 10;
			borrow = 1;
		} else {
			borrow = 0;
		}
		res[i] = diff;
	}
	trim_poly(res);
	return res;
}

// ============================================================================
// 5. ВЫСШАЯ АЛГЕБРА И ЛИНАЛ: МЕТОД ТООМА–КУКА (TOOM-3) — O(n^(log_3 5))
// ============================================================================
//
// Математическая основа (интерполяция Лагранжа + СЛАУ с матрицей Вандермонда):
//   1) Упакуем цифры по 4 разряда (база B = 10^4 = 10000).
//   2) Разрежем каждое длинное число на 3 части длины k блоков (положим X = B^k):
//        A(X) = a_2 X^2 + a_1 X + a_0,
//        B(X) = b_2 X^2 + b_1 X + b_0.
//   3) Произведение C(X) = A(X) * B(X) = c_4 X^4 + c_3 X^3 + c_2 X^2 + c_1 X + c_0 —
//      многочлен степени <= 4, который по теореме единственности интерполяционного полинома
//      однозначно определяется своими значениями в 5 узлах интерполяции:
//        x_0 = 0,  x_1 = 1,  x_2 = -1,  x_3 = -2,  x_4 = inf (старший коэффициент).
//
//   4) Используем симметрию узлов {1, -1} относительно 0 (см. vmath.ru/vf5/interpolation/symm):
//        p_0 = a_0 + a_2,
//        A(0)   = a_0,
//        A(1)   = p_0 + a_1,
//        A(-1)  = p_0 - a_1,
//        A(-2)  = 2 * (A(-1) + a_2) - a_0 = a_0 - 2 a_1 + 4 a_2,
//        A(inf) = a_2.
//
//   5) Перемножаем 5 пар значений рекурсивно: y_i = A(x_i) * B(x_i) (всего 5 умножений вместо 9!).
//
//   6) Решаем СЛАУ Вандермонда V * c = y методом Гаусса (последовательность Бодрато, всего 1 точное
//      деление на 3 и деления на 2):
//        V = [ 1   0   0   0   0 ]     [ c_0 ]   [ y_0   ]
//            [ 1   1   1   1   1 ]     [ c_1 ]   [ y_1   ]
//            [ 1  -1   1  -1   1 ]  *  [ c_2 ] = [ y_-1  ]
//            [ 1  -2   4  -8  16 ]     [ c_3 ]   [ y_-2  ]
//            [ 0   0   0   0   1 ]     [ c_4 ]   [ y_inf ]
//
//      Пошаговое исключение Гаусса (каждое деление гарантированно нацело в Z!):
//        c_0 = y_0
//        c_4 = y_inf
//        r_3 = (y_-2 - y_1) / 3         -- т.к. y_-2 - y_1 = -3 c_1 + 3 c_2 - 9 c_3 + 15 c_4 (кратно 3!)
//        r_1 = (y_1 - y_-1) / 2         -- полуразность: c_1 + c_3
//        r_2 = y_-1 - c_0               -- -c_1 + c_2 - c_3 + c_4
//        r_3 = (r_2 - r_3) / 2 + 2 c_4  -- даёт ровно c_3!
//        c_2 = r_2 + r_1 - c_4          -- даёт ровно c_2!
//        c_1 = r_1 - r_3                -- даёт ровно c_1!
//        c_3 = r_3

void LongNumber::normalize_limbs(std::vector<std::int64_t>& limbs) {
	while (limbs.size() > 1 && limbs.back() == 0) {
		limbs.pop_back();
	}
	if (limbs.empty()) {
		limbs.push_back(0);
	}
}

int LongNumber::compare_limbs(
	const std::vector<std::int64_t>& a,
	const std::vector<std::int64_t>& b
) noexcept {
	if (a.size() != b.size()) {
		return (a.size() > b.size()) ? 1 : -1;
	}
	for (int i = static_cast<int>(a.size()) - 1; i >= 0; i--) {
		if (a[i] != b[i]) {
			return (a[i] > b[i]) ? 1 : -1;
		}
	}
	return 0;
}

std::vector<std::int64_t> LongNumber::add_limbs(
	const std::vector<std::int64_t>& a,
	const std::vector<std::int64_t>& b
) {
	const std::size_t n = std::max(a.size(), b.size());
	std::vector<std::int64_t> res;
	res.reserve(n + 1);
	std::int64_t carry = 0;
	for (std::size_t i = 0; i < n || carry > 0; i++) {
		std::int64_t cur = carry;
		if (i < a.size()) cur += a[i];
		if (i < b.size()) cur += b[i];
		res.push_back(cur % TOOM_BASE);
		carry = cur / TOOM_BASE;
	}
	normalize_limbs(res);
	return res;
}

std::vector<std::int64_t> LongNumber::sub_limbs(
	const std::vector<std::int64_t>& a,
	const std::vector<std::int64_t>& b
) {
	// Предполагается |a| >= |b|
	std::vector<std::int64_t> res(a.size(), 0);
	std::int64_t borrow = 0;
	for (std::size_t i = 0; i < a.size(); i++) {
		std::int64_t diff = a[i] - borrow - (i < b.size() ? b[i] : 0);
		if (diff < 0) {
			diff += TOOM_BASE;
			borrow = 1;
		} else {
			borrow = 0;
		}
		res[i] = diff;
	}
	normalize_limbs(res);
	return res;
}

LongNumber::SignedLimbs LongNumber::add_signed(const SignedLimbs& a, const SignedLimbs& b) {
	if (a.limbs.size() == 1 && a.limbs[0] == 0) return b;
	if (b.limbs.size() == 1 && b.limbs[0] == 0) return a;

	if (a.sign == b.sign) {
		return {a.sign, add_limbs(a.limbs, b.limbs)};
	}
	const int cmp = compare_limbs(a.limbs, b.limbs);
	if (cmp == 0) {
		return {1, {0}};
	}
	if (cmp > 0) {
		return {a.sign, sub_limbs(a.limbs, b.limbs)};
	}
	return {b.sign, sub_limbs(b.limbs, a.limbs)};
}

LongNumber::SignedLimbs LongNumber::sub_signed(const SignedLimbs& a, const SignedLimbs& b) {
	if (b.limbs.size() == 1 && b.limbs[0] == 0) return a;
	return add_signed(a, {-b.sign, b.limbs});
}

LongNumber::SignedLimbs LongNumber::mul_scalar_signed(const SignedLimbs& a, std::int64_t k) {
	if (k == 0 || (a.limbs.size() == 1 && a.limbs[0] == 0)) {
		return {1, {0}};
	}
	const int out_sign = (k < 0) ? -a.sign : a.sign;
	const std::int64_t abs_k = (k < 0) ? -k : k;

	std::vector<std::int64_t> res;
	res.reserve(a.limbs.size() + 1);
	std::int64_t carry = 0;
	for (std::size_t i = 0; i < a.limbs.size() || carry > 0; i++) {
		const std::int64_t cur = carry + (i < a.limbs.size() ? a.limbs[i] * abs_k : 0);
		res.push_back(cur % TOOM_BASE);
		carry = cur / TOOM_BASE;
	}
	normalize_limbs(res);
	return {out_sign, std::move(res)};
}

LongNumber::SignedLimbs LongNumber::div_exact_scalar_signed(const SignedLimbs& a, std::int64_t k) {
	// Деление на константу k (в Тооме-3 это k = 2 или k = 3), которое алгебраически гарантированно делится нацело!
	if (a.limbs.size() == 1 && a.limbs[0] == 0) {
		return {1, {0}};
	}
	std::vector<std::int64_t> res(a.limbs.size(), 0);
	std::int64_t rem = 0;
	for (int i = static_cast<int>(a.limbs.size()) - 1; i >= 0; i--) {
		const std::int64_t cur = rem * TOOM_BASE + a.limbs[i];
		res[i] = cur / k;
		rem = cur % k;
	}
	normalize_limbs(res);
	const int out_sign = (res.size() == 1 && res[0] == 0) ? 1 : a.sign;
	return {out_sign, std::move(res)};
}

std::vector<std::int64_t> LongNumber::pack_to_base10000(const std::vector<int>& dec_digits) {
	std::vector<std::int64_t> limbs((dec_digits.size() + TOOM_DIGITS_PER_LIMB - 1) / TOOM_DIGITS_PER_LIMB, 0);
	for (std::size_t i = 0; i < dec_digits.size(); i += TOOM_DIGITS_PER_LIMB) {
		std::int64_t val = 0;
		std::int64_t mult = 1;
		for (int j = 0; j < TOOM_DIGITS_PER_LIMB && (i + j) < dec_digits.size(); j++) {
			val += static_cast<std::int64_t>(dec_digits[i + j]) * mult;
			mult *= 10;
		}
		limbs[i / TOOM_DIGITS_PER_LIMB] = val;
	}
	normalize_limbs(limbs);
	return limbs;
}

std::vector<int> LongNumber::unpack_from_base10000(const std::vector<std::int64_t>& limbs) {
	if (limbs.size() == 1 && limbs[0] == 0) {
		return {0};
	}
	std::vector<int> dec;
	dec.reserve(limbs.size() * TOOM_DIGITS_PER_LIMB);
	for (std::size_t i = 0; i < limbs.size(); i++) {
		std::int64_t val = limbs[i];
		for (int j = 0; j < TOOM_DIGITS_PER_LIMB; j++) {
			dec.push_back(static_cast<int>(val % 10));
			val /= 10;
		}
	}
	trim_poly(dec);
	return dec;
}

std::vector<std::int64_t> LongNumber::multiply_limbs_naive(
	const std::vector<std::int64_t>& a,
	const std::vector<std::int64_t>& b
) {
	if ((a.size() == 1 && a[0] == 0) || (b.size() == 1 && b[0] == 0)) {
		return {0};
	}
	std::vector<std::int64_t> res(a.size() + b.size() + 1, 0);
	for (std::size_t i = 0; i < a.size(); i++) {
		std::int64_t carry = 0;
		for (std::size_t j = 0; j < b.size(); j++) {
			const std::int64_t cur = res[i + j] + a[i] * b[j] + carry;
			res[i + j] = cur % TOOM_BASE;
			carry = cur / TOOM_BASE;
		}
		std::size_t pos = i + b.size();
		while (carry > 0) {
			const std::int64_t cur = res[pos] + carry;
			res[pos] = cur % TOOM_BASE;
			carry = cur / TOOM_BASE;
			pos++;
		}
	}
	normalize_limbs(res);
	return res;
}

LongNumber::SignedLimbs LongNumber::multiply_signed_toom3(const SignedLimbs& a, const SignedLimbs& b) {
	if ((a.limbs.size() == 1 && a.limbs[0] == 0) || (b.limbs.size() == 1 && b.limbs[0] == 0)) {
		return {1, {0}};
	}
	std::vector<std::int64_t> prod = multiply_limbs_toom3(a.limbs, b.limbs);
	const int out_sign = (prod.size() == 1 && prod[0] == 0) ? 1 : (a.sign * b.sign);
	return {out_sign, std::move(prod)};
}

std::vector<std::int64_t> LongNumber::multiply_limbs_toom3(
	const std::vector<std::int64_t>& a,
	const std::vector<std::int64_t>& b
) {
	if ((a.size() == 1 && a[0] == 0) || (b.size() == 1 && b[0] == 0)) {
		return {0};
	}

	// База рекурсии: для коротких многочленов используем быстрый метод без аллокаций подзадач
	if (std::min(a.size(), b.size()) < TOOM3_THRESHOLD) {
		return multiply_limbs_naive(a, b);
	}

	// 1. Разрезаем многочлены A и B на 3 части по k блоков: A(X) = a2 * X^2 + a1 * X + a0, X = B^k
	const std::size_t max_len = std::max(a.size(), b.size());
	const std::size_t k = (max_len + 2) / 3;

	auto slice_part = [](const std::vector<std::int64_t>& v, std::size_t start, std::size_t len) -> SignedLimbs {
		if (start >= v.size()) {
			return {1, {0}};
		}
		const std::size_t end = std::min(v.size(), start + len);
		std::vector<std::int64_t> part(v.begin() + start, v.begin() + end);
		normalize_limbs(part);
		return {1, std::move(part)};
	};

	const SignedLimbs a0 = slice_part(a, 0, k);
	const SignedLimbs a1 = slice_part(a, k, k);
	const SignedLimbs a2 = slice_part(a, 2 * k, k);

	const SignedLimbs b0 = slice_part(b, 0, k);
	const SignedLimbs b1 = slice_part(b, k, k);
	const SignedLimbs b2 = slice_part(b, 2 * k, k);

	// 2. Вычисляем значения многочленов A(x) и B(x) в 5 узлах интерполяции {0, 1, -1, -2, inf}
	// Симметрия узлов {1, -1}: p0 = a0 + a2 => A(1) = p0 + a1, A(-1) = p0 - a1
	const SignedLimbs p0 = add_signed(a0, a2);
	const SignedLimbs a_at_0    = a0;
	const SignedLimbs a_at_1    = add_signed(p0, a1);
	const SignedLimbs a_at_m1   = sub_signed(p0, a1);
	const SignedLimbs a_at_m2   = sub_signed(mul_scalar_signed(add_signed(a_at_m1, a2), 2), a0);
	const SignedLimbs a_at_inf  = a2;

	const SignedLimbs q0 = add_signed(b0, b2);
	const SignedLimbs b_at_0    = b0;
	const SignedLimbs b_at_1    = add_signed(q0, b1);
	const SignedLimbs b_at_m1   = sub_signed(q0, b1);
	const SignedLimbs b_at_m2   = sub_signed(mul_scalar_signed(add_signed(b_at_m1, b2), 2), b0);
	const SignedLimbs b_at_inf  = b2;

	// 3. 5 рекурсивных умножений вместо 9: значения произведения C(x_i) = A(x_i) * B(x_i)
	const SignedLimbs y_0   = multiply_signed_toom3(a_at_0,   b_at_0);
	const SignedLimbs y_1   = multiply_signed_toom3(a_at_1,   b_at_1);
	const SignedLimbs y_m1  = multiply_signed_toom3(a_at_m1,  b_at_m1);
	const SignedLimbs y_m2  = multiply_signed_toom3(a_at_m2,  b_at_m2);
	const SignedLimbs y_inf = multiply_signed_toom3(a_at_inf, b_at_inf);

	// 4. Интерполяция (обращение 5x5 матрицы Вандермонда методом Гаусса / схема Бодрато):
	// Восстанавливаем точные коэффициенты C(X) = c4*X^4 + c3*X^3 + c2*X^2 + c1*X + c0
	const SignedLimbs c0 = y_0;
	const SignedLimbs c4 = y_inf;

	SignedLimbs r3 = div_exact_scalar_signed(sub_signed(y_m2, y_1), 3);
	SignedLimbs r1 = div_exact_scalar_signed(sub_signed(y_1, y_m1), 2);
	SignedLimbs r2 = sub_signed(y_m1, c0);

	r3 = add_signed(div_exact_scalar_signed(sub_signed(r2, r3), 2), mul_scalar_signed(c4, 2));
	const SignedLimbs c2 = sub_signed(add_signed(r2, r1), c4);
	const SignedLimbs c1 = sub_signed(r1, r3);
	const SignedLimbs c3 = r3;

	// 5. Подстановка X = B^k (сборка итогового числа со сдвигами 0, k, 2k, 3k, 4k и пробросом переносов)
	std::vector<std::int64_t> result(4 * k + c4.limbs.size() + 2, 0);
	auto add_shifted = [&result](const SignedLimbs& coeff, std::size_t offset) {
		if (coeff.limbs.size() == 1 && coeff.limbs[0] == 0) {
			return;
		}
		for (std::size_t i = 0; i < coeff.limbs.size(); i++) {
			if (offset + i >= result.size()) {
				result.resize(offset + i + 2, 0);
			}
			result[offset + i] += static_cast<std::int64_t>(coeff.sign) * coeff.limbs[i];
		}
	};

	add_shifted(c0, 0);
	add_shifted(c1, k);
	add_shifted(c2, 2 * k);
	add_shifted(c3, 3 * k);
	add_shifted(c4, 4 * k);

	// Финальная нормализация переносов в базе B = 10^4
	std::int64_t carry = 0;
	for (std::size_t i = 0; i < result.size(); i++) {
		std::int64_t cur = result[i] + carry;
		std::int64_t rem = cur % TOOM_BASE;
		carry = cur / TOOM_BASE;
		if (rem < 0) {
			rem += TOOM_BASE;
			carry -= 1;
		}
		result[i] = rem;
	}
	while (carry > 0) {
		result.push_back(carry % TOOM_BASE);
		carry /= TOOM_BASE;
	}
	normalize_limbs(result);
	return result;
}

std::vector<int> LongNumber::multiply_poly(const std::vector<int>& a, const std::vector<int>& b) {
	if ((a.size() == 1 && a[0] == 0) || (b.size() == 1 && b[0] == 0)) {
		return {0};
	}
	const std::vector<std::int64_t> la = pack_to_base10000(a);
	const std::vector<std::int64_t> lb = pack_to_base10000(b);
	const std::vector<std::int64_t> prod_limbs = multiply_limbs_toom3(la, lb);
	return unpack_from_base10000(prod_limbs);
}

// ============================================================================
// 6. МАТЕМАТИЧЕСКИЙ АНАЛИЗ: ДЕЛЕНИЕ МЕТОДОМ НЬЮТОНА–РАФСОНА O(M(n))
// ============================================================================
//
// Ищем корень нелинейного уравнения f(x) = 1/x - V = 0 методом касательных Ньютона:
//     x_{k+1} = x_k * (2 - V * x_k),
// используя наше умножение Тоома–Кука multiply_poly(...) на каждом шаге удвоения точности!

std::vector<int> LongNumber::shift_right_digits(const std::vector<int>& poly, int k) {
	if (k <= 0) {
		return poly;
	}
	if (static_cast<std::size_t>(k) >= poly.size()) {
		return {0};
	}
	std::vector<int> res(poly.begin() + k, poly.end());
	trim_poly(res);
	return res;
}

std::vector<int> LongNumber::shift_left_digits(const std::vector<int>& poly, int k) {
	if (k <= 0 || (poly.size() == 1 && poly[0] == 0)) {
		return poly;
	}
	std::vector<int> res(static_cast<std::size_t>(k), 0);
	res.insert(res.end(), poly.begin(), poly.end());
	return res;
}

std::pair<std::vector<int>, std::vector<int>> LongNumber::divmod_knuth_small(
	const std::vector<int>& u,
	const std::vector<int>& v
) {
	const int cmp = compare_abs(u, v);
	if (cmp < 0) {
		return {{0}, u};
	}
	if (cmp == 0) {
		return {{1}, {0}};
	}

	std::vector<std::vector<int>> v_mult(10);
	v_mult[0].push_back(0);
	for (int d = 1; d <= 9; d++) {
		v_mult[d] = add_poly(v_mult[d - 1], v);
	}

	std::vector<int> q(u.size(), 0);
	std::vector<int> rem(1, 0);

	for (int i = static_cast<int>(u.size()) - 1; i >= 0; i--) {
		rem = shift_left_digits(rem, 1);
		rem[0] = u[i];
		trim_poly(rem);

		int low = 0, high = 9, best = 0;
		while (low <= high) {
			const int mid = (low + high) / 2;
			if (compare_abs(v_mult[mid], rem) <= 0) {
				best = mid;
				low = mid + 1;
			} else {
				high = mid - 1;
			}
		}
		q[i] = best;
		if (best > 0) {
			rem = sub_poly(rem, v_mult[best]);
		}
	}
	trim_poly(q);
	trim_poly(rem);
	return {q, rem};
}

std::vector<int> LongNumber::newton_reciprocal(const std::vector<int>& v, int target_precision) {
	const int m = static_cast<int>(v.size());
	const int init_take = std::min(m, 15);
	std::uint64_t top_v = 0;
	for (int i = m - 1; i >= m - init_take; i--) {
		top_v = top_v * 10ULL + static_cast<std::uint64_t>(v[i]);
	}

	const int init_prec = 4;
	std::uint64_t num = 1;
	for (int i = 0; i < init_prec + init_take; i++) {
		num *= 10ULL;
	}
	std::uint64_t x0_val = num / top_v;

	std::vector<int> x;
	while (x0_val > 0) {
		x.push_back(static_cast<int>(x0_val % 10ULL));
		x0_val /= 10ULL;
	}
	trim_poly(x);
	int cur_prec = init_prec;

	std::vector<int> precisions;
	for (int p = target_precision + 4; p > cur_prec; p = (p + 1) / 2 + 1) {
		precisions.push_back(p);
	}
	std::reverse(precisions.begin(), precisions.end());

	for (int next_prec : precisions) {
		const int take = std::min(m, next_prec + 4);
		const std::vector<int> v_slice(v.end() - take, v.end());

		const std::vector<int> vx = multiply_poly(v_slice, x);

		std::vector<int> two_scaled(static_cast<std::size_t>(cur_prec + take + 1), 0);
		two_scaled.back() = 2;

		if (compare_abs(two_scaled, vx) > 0) {
			const std::vector<int> diff = sub_poly(two_scaled, vx);
			const std::vector<int> prod = multiply_poly(x, diff);
			x = shift_right_digits(prod, 2 * cur_prec + take - next_prec);
		} else {
			x = shift_left_digits(x, next_prec - cur_prec);
		}
		cur_prec = next_prec;
	}

	return shift_right_digits(x, cur_prec - target_precision);
}

std::pair<std::vector<int>, std::vector<int>> LongNumber::divmod_poly(
	const std::vector<int>& u,
	const std::vector<int>& v
) {
	const int cmp = compare_abs(u, v);
	if (cmp < 0) {
		return {{0}, u};
	}
	if (cmp == 0) {
		return {{1}, {0}};
	}

	const int n = static_cast<int>(u.size());
	const int m = static_cast<int>(v.size());
	const int q_digits = n - m + 1;

	if (q_digits < 48 && n < 96) {
		return divmod_knuth_small(u, v);
	}

	const int target_prec = q_digits + 4;
	const std::vector<int> inv_v = newton_reciprocal(v, target_prec);

	std::vector<int> q = shift_right_digits(multiply_poly(u, inv_v), m + target_prec);
	std::vector<int> qv = multiply_poly(q, v);

	if (compare_abs(qv, u) > 0) {
		std::vector<int> deficit = sub_poly(qv, u);
		auto [corr_q, corr_r] = divmod_knuth_small(deficit, v);
		if (!(corr_r.size() == 1 && corr_r[0] == 0)) {
			corr_q = add_poly(corr_q, {1});
		}
		q = sub_poly(q, corr_q);
		qv = multiply_poly(q, v);
	}

	std::vector<int> rem = sub_poly(u, qv);
	if (compare_abs(rem, v) >= 0) {
		auto [extra_q, final_rem] = divmod_poly(rem, v);
		q = add_poly(q, extra_q);
		rem = final_rem;
	}

	trim_poly(q);
	trim_poly(rem);
	return {q, rem};
}

// ============================================================================
// 7. ВЫВОД В ПОТОК
// ============================================================================

namespace yenni {
	std::ostream& operator << (std::ostream& os, const LongNumber& x) {
		if (x.numbers == nullptr || x.length == 0) {
			return os;
		}
		if (x.sign == 1) {
			os << "-";
		}
		for (int i = 0; i < x.length - x.sign; i++) {
			os << x.numbers[i];
		}
		return os;
	}
}
