#include <gtest/gtest.h>

#include <chrono>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "long_nums.hpp"

using yenni::LongNumber;

namespace {
	std::string to_str(const LongNumber& n) {
		std::ostringstream oss;
		oss << n;
		return oss.str();
	}

	std::string random_number_string(std::mt19937& rng, int digits, bool negative = false) {
		std::uniform_int_distribution<int> first_dist(1, 9);
		std::uniform_int_distribution<int> digit_dist(0, 9);

		std::string s;
		s.reserve(static_cast<std::size_t>(digits) + 1);
		if (negative) {
			s.push_back('-');
		}
		s.push_back(static_cast<char>('0' + first_dist(rng)));
		for (int i = 1; i < digits; i++) {
			s.push_back(static_cast<char>('0' + digit_dist(rng)));
		}
		return s;
	}
}

// 1. Проверка исправленных багов из старой реализации
TEST(BugFixes, IntConstructorAndStringAssignment) {
	EXPECT_EQ(LongNumber(0), LongNumber("0"));
	EXPECT_EQ(LongNumber(42), LongNumber("42"));
	EXPECT_EQ(LongNumber(-42), LongNumber("-42"));
	EXPECT_EQ(LongNumber(-19602), LongNumber("-19602"));

	LongNumber x("12345");
	x = "-98765";
	EXPECT_EQ(x, LongNumber("-98765"));
	EXPECT_EQ(to_str(x), "-98765");

	LongNumber z("-0000");
	EXPECT_EQ(z, LongNumber(0));
	EXPECT_EQ(to_str(z), "0");
}

// 2. Проверка умножения Тоома–Кука (Toom-3 / интерполяция Лагранжа)
// через алгебраическое тождество A^2 - B^2 == (A - B) * (A + B) на многоуровневой рекурсии
TEST(ToomCookLagrange, DifferenceOfSquaresMultiLevelRecursion) {
	std::mt19937 rng(20261122);
	const int sizes[] = {80, 250, 750, 1500}; // 1, 2, 3 и 4 уровня рекурсии Toom-3!
	for (int d : sizes) {
		LongNumber A(random_number_string(rng, d).c_str());
		LongNumber B(random_number_string(rng, d - 7).c_str());

		LongNumber lhs = (A * A) - (B * B);
		LongNumber rhs = (A - B) * (A + B);
		EXPECT_EQ(lhs, rhs) << "Mismatch at digit size " << d;
	}
}

TEST(ToomCookLagrange, AsymmetricLengthsAndMaxCarries) {
	// Сильно разные длины (где старшие куски a2 или b2 оказываются нулевыми!)
	std::mt19937 rng(424242);
	LongNumber big(random_number_string(rng, 900).c_str());
	LongNumber med(random_number_string(rng, 110).c_str());
	LongNumber one(1);
	// Дистрибутивность: big * (med + 1) == big * med + big
	EXPECT_EQ(big * (med + one), (big * med) + big);

	// Худший случай переносов: (10^400 - 1) * (10^300 - 1)
	std::string nines_400(400, '9');
	std::string nines_300(300, '9');
	LongNumber a(nines_400.c_str());
	LongNumber b(nines_300.c_str());

	LongNumber pow400 = a + one;
	LongNumber pow300 = b + one;
	LongNumber expected = (pow400 * pow300) - pow400 - pow300 + one;
	EXPECT_EQ(a * b, expected);
}

// 3. Проверка деления Ньютона–Рафсона поверх Тоома–Кука: A == B * (A / B) + (A % B) и 0 <= R < |B|
TEST(NewtonDivision, EuclideanIdentityLargeNumbers) {
	std::mt19937 rng(31415926);

	const int sizes[][2] = {
		{40, 15},
		{120, 55},
		{350, 120},
		{700, 260},
		{1200, 415},
		{900, 899},
		{900, 3}
	};

	for (const auto& [n_digits, m_digits] : sizes) {
		for (bool neg_a : {false, true}) {
			for (bool neg_b : {false, true}) {
				LongNumber A(random_number_string(rng, n_digits, neg_a).c_str());
				LongNumber B(random_number_string(rng, m_digits, neg_b).c_str());
				LongNumber abs_B(to_str(B).front() == '-' ? to_str(B).c_str() + 1 : to_str(B).c_str());

				LongNumber Q = A / B;
				LongNumber R = A % B;

				EXPECT_EQ(B * Q + R, A)
					<< "Failed Euclidean identity for lengths (" << n_digits << ", " << m_digits
					<< "), signs (" << neg_a << ", " << neg_b << ")";

				EXPECT_FALSE(R < LongNumber(0));
				EXPECT_TRUE(R < abs_B);
			}
		}
	}
}

TEST(NewtonDivision, ExactQuotientAndBoundaryCases) {
	std::string divisor_str = "9876543210123456789098765432101234567890123456789";
	std::string exact_q_str(300, '9');

	LongNumber V(divisor_str.c_str());
	LongNumber Q_exact(exact_q_str.c_str());
	LongNumber U = V * Q_exact;

	EXPECT_EQ(U / V, Q_exact);
	EXPECT_EQ(U % V, LongNumber(0));

	LongNumber U_minus_1 = U - LongNumber(1);
	EXPECT_EQ(U_minus_1 / V, Q_exact - LongNumber(1));
	EXPECT_EQ(U_minus_1 % V, V - LongNumber(1));

	LongNumber U_plus_1 = U + LongNumber(1);
	EXPECT_EQ(U_plus_1 / V, Q_exact);
	EXPECT_EQ(U_plus_1 % V, LongNumber(1));
}

// 4. Мини-бенчмарк Тоом–Кук + Ньютон–Рафсон на числах по 20 000 цифр
TEST(Performance, LargeMultiplyAndDivide20kDigits) {
	std::mt19937 rng(777);
	LongNumber A20k(random_number_string(rng, 20000).c_str());
	LongNumber B20k(random_number_string(rng, 20000).c_str());

	auto t0 = std::chrono::steady_clock::now();
	LongNumber P = A20k * B20k; // Результат: 40 000 цифр!
	auto t1 = std::chrono::steady_clock::now();

	LongNumber Q = P / A20k; // Обратное деление 40 000-значного числа на 20 000-значное!
	auto t2 = std::chrono::steady_clock::now();

	EXPECT_EQ(Q, B20k);

	const double mul_ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
	const double div_ms = std::chrono::duration<double, std::milli>(t2 - t1).count();
	std::cout << "[ BENCHMARK ] 20,000 x 20,000 digits Toom-Cook (Toom-3) multiplication: " << mul_ms << " ms\n";
	std::cout << "[ BENCHMARK ] 40,000 / 20,000 digits Newton-Raphson division: " << div_ms << " ms\n";
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
