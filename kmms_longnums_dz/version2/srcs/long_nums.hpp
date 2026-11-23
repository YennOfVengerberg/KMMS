#ifndef LONG_NUMS_HPP
#define LONG_NUMS_HPP

#include <cstdint>
#include <iostream>
#include <vector>

namespace yenni {
	class LongNumber {
		private:
			int* numbers;
			int length;
			int sign;

		public:
			LongNumber();
			LongNumber(int length, int sign);
			LongNumber(int num);
			LongNumber(const char* const str);
			LongNumber(const LongNumber& x);
			LongNumber(LongNumber&& x) noexcept;

			~LongNumber();

			LongNumber& operator = (const char* const str);
			LongNumber& operator = (const LongNumber& x);
			LongNumber& operator = (LongNumber&& x) noexcept;

			bool operator == (const LongNumber& x) const;
			bool operator != (const LongNumber& x) const;
			bool operator > (const LongNumber& x) const;
			bool operator < (const LongNumber& x) const;

			LongNumber operator + (const LongNumber& x) const;
			LongNumber operator - (const LongNumber& x) const;
			LongNumber operator * (const LongNumber& x) const;
			LongNumber operator / (const LongNumber& x) const;
			LongNumber operator % (const LongNumber& x) const;

			friend std::ostream& operator << (std::ostream& os, const LongNumber& x);

		private:
			// --- Вспомогательные методы представления и знака ---
			int digits_count() const noexcept;
			bool is_zero() const noexcept;
			static int compare_abs(const std::vector<int>& a, const std::vector<int>& b) noexcept;
			bool left_bigger_abs(const LongNumber& a, const LongNumber& b) const;
			bool eq_abs(const LongNumber& a, const LongNumber& b) const;
			LongNumber abs_val(const LongNumber& inp) const;
			int get_sign(const char* const str) const noexcept;
			int get_length(const char* const str) const noexcept;

			// Перевод между старшими разрядами вперёд (big-endian, база 10)
			// и коэффициентами многочлена P(x) = sum c_k x^k (little-endian, младшие вперёд)
			std::vector<int> to_poly_digits() const;
			static LongNumber from_poly_digits(const std::vector<int>& poly, int result_sign);

			// --- Линейные операции над модулями O(n) ---
			static std::vector<int> add_poly(const std::vector<int>& a, const std::vector<int>& b);
			static std::vector<int> sub_poly(const std::vector<int>& a, const std::vector<int>& b);
			static void trim_poly(std::vector<int>& poly);

			// --- Высшая алгебра и Линал: умножение Тоома–Кука (Toom-3) через интерполяцию Лагранжа ---
			// Работает в упакованной базе B = 10^4 = 10000 для малых констант,
			// рекурсивно интерполируя произведение квадратных трёхчленов по 5 узлам {0, 1, -1, -2, inf}.
			static constexpr std::int64_t TOOM_BASE = 10000LL;
			static constexpr int TOOM_DIGITS_PER_LIMB = 4;
			static constexpr std::size_t TOOM3_THRESHOLD = 18; // 18 блоков по 4 цифры = 72 десятичных разряда

			struct SignedLimbs {
				int sign = 1; // +1 или -1 (для нуля +1)
				std::vector<std::int64_t> limbs; // коэффициенты в базе 10^4 (младшие вперёд)
			};

			static void normalize_limbs(std::vector<std::int64_t>& limbs);
			static int compare_limbs(const std::vector<std::int64_t>& a, const std::vector<std::int64_t>& b) noexcept;
			static std::vector<std::int64_t> add_limbs(
				const std::vector<std::int64_t>& a,
				const std::vector<std::int64_t>& b
			);
			static std::vector<std::int64_t> sub_limbs(
				const std::vector<std::int64_t>& a,
				const std::vector<std::int64_t>& b
			);
			static SignedLimbs add_signed(const SignedLimbs& a, const SignedLimbs& b);
			static SignedLimbs sub_signed(const SignedLimbs& a, const SignedLimbs& b);
			static SignedLimbs mul_scalar_signed(const SignedLimbs& a, std::int64_t k);
			static SignedLimbs div_exact_scalar_signed(const SignedLimbs& a, std::int64_t k);

			static std::vector<std::int64_t> pack_to_base10000(const std::vector<int>& dec_digits);
			static std::vector<int> unpack_from_base10000(const std::vector<std::int64_t>& limbs);

			static std::vector<std::int64_t> multiply_limbs_naive(
				const std::vector<std::int64_t>& a,
				const std::vector<std::int64_t>& b
			);
			static std::vector<std::int64_t> multiply_limbs_toom3(
				const std::vector<std::int64_t>& a,
				const std::vector<std::int64_t>& b
			);
			static SignedLimbs multiply_signed_toom3(const SignedLimbs& a, const SignedLimbs& b);
			static std::vector<int> multiply_poly(const std::vector<int>& a, const std::vector<int>& b);

			// --- Матанализ: деление методом Ньютона–Рафсона O(M(n)) ---
			// Нахождение корня f(x) = 1/x - V = 0 итерацией x_{k+1} = x_k * (2 - V * x_k)
			static std::vector<int> shift_right_digits(const std::vector<int>& poly, int k);
			static std::vector<int> shift_left_digits(const std::vector<int>& poly, int k);
			static std::vector<int> newton_reciprocal(const std::vector<int>& v, int target_precision);
			static std::pair<std::vector<int>, std::vector<int>> divmod_poly(
				const std::vector<int>& u,
				const std::vector<int>& v
			);
			static std::pair<std::vector<int>, std::vector<int>> divmod_knuth_small(
				const std::vector<int>& u,
				const std::vector<int>& v
			);
	};
}

#endif
