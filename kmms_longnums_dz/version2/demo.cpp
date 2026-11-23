#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

#include "long_nums.hpp"

using yenni::LongNumber;

static void show(const char* title, const LongNumber& r) {
    std::cout << "  " << title << " = " << r << "\n";
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001); // чтобы русский текст в консоли не превращался в кракозябры
#endif

    std::cout << "=== КОНТРОЛЬНЫЙ ПРИМЕР: АРИФМЕТИКА ДЛИННЫХ ЧИСЕЛ ===\n\n";

    LongNumber a("123456789012345678901234567890");
    LongNumber b("987654321987654321");
    std::cout << "A = " << a << "\nB = " << b << "\n\n";

    show("A + B", a + b);
    show("A - B", a - b);
    show("A * B", a * b);
    show("A / B", a / b);
    show("A % B", a % b);

    std::cout << "\n=== ПРОВЕРКА ЗНАКОВ (евклидово деление) ===\n";
    LongNumber p("-500"), q("7");
    show("-500 / 7 ", p / q);
    show("-500 % 7 ", p % q);
    show(" 500 / -7", LongNumber("500") / LongNumber("-7"));
    show(" 500 % -7", LongNumber("500") % LongNumber("-7"));
    show("-500 / -7", p / LongNumber("-7"));
    show("-500 % -7", p % LongNumber("-7"));

    std::cout << "\n=== КРУПНЫЕ ЧИСЛА (умножение Тоома-Кука, деление Ньютона) ===\n";
    std::string s1 = "98765432109876543210987654321098765432109876543210";
    std::string s2 = "12345678901234567890123456789012345678901234567890";
    LongNumber x(s1.c_str()), y(s2.c_str());
    LongNumber z = x * y;

    std::cout << "X = " << x << "\nY = " << y << "\n";
    show("X * Y", z);
    show("(X * Y) / Y", z / y);
    std::cout << "\n  (X * Y) / Y == X ?  " << ((z / y) == x ? "ДА" : "НЕТ") << "\n";

    std::cout << "\nЗавершено успешно.\n";
    return 0;
}