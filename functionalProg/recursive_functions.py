# 1 Базовая форма
# 2 Рекуррентная
def fact(n):
    if n == 1 or n == 0:
        return 1
    else: 
        return n * fact(n-1)

print(fact(5))
#fact(5) -> fact(4) -> 3 -> 2 -> 1.

s = 1
for i in range (1, 6):
    s *= i
print(s)