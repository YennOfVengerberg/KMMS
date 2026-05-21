# Первого порядка - принимает переменную и возвращает какую-то переменную

# Высших порядков - принимает на вход функцию, и возвращает функцию

# Функции высших порядков(e.g.) : map, filter, reduce



array1 = [1, 2, 3, 4, 7, 30, 19, 22, 9, 3]
def func1(arg): 
    if arg > 10:
        return arg

print(list(filter(func1, array1)))
# исключительно фильтрация по критерию без изменения данных

def func2(arg):
    if(arg % 2 == 0):
        return arg **2
    else:
        return arg * (-1)

print(list(map(func2, array1)))

### действие по всему массиву каждый элемент

x = list(filter(func1, array1))
print(list(map(func2, x)))

### 

from functools import reduce

def func3(arg1, arg2):
    return arg1 * arg2

print(reduce(func3, array1))

# действие по всему массиву, на выходе одно значение

print(reduce(lambda x, y: x * y, array1))

print(list(map(lambda x: x**2, array1)))

print(list(filter(lambda x: x > 10, array1)))