
### https://docs.google.com/document/d/17FqU3IPmJKPDp60bMCKDmmWpanj-BBYS8nhD4q1CaJk/mobilebasic

students = [
   {"name": "Alice", "age": 20, "grades": [85, 90, 88, 92]},
   {"name": "Bob", "age": 22, "grades": [78, 89, 76, 85]},
   {"name": "Charlie", "age": 21, "grades": [92, 95, 88, 94]},
   {"name": "Diana", "age": 19, "grades": [90, 92, 95, 98]},
]

### 1.1

age_criteria = 18 ###int(input("input age criteria: "))

filtered = list(filter(lambda student_age: student_age["age"] > age_criteria, students))

print(filtered)

### 1.2
from functools import reduce

students_with_avg = list(
    map(
        lambda s: {
            **s,
            "avg_grade": reduce(lambda a, b: a + b, s["grades"])
            / len(s["grades"]),
        },
        students,
    )
)
print("students_avgs: ")
for student_avg in students_with_avg:
    print(f"{student_avg['name'],}: {student_avg['avg_grade']}")

total_grades_sum = reduce(
    lambda acc, s: acc + s["avg_grade"], students_with_avg, 0
)

overall_avg = total_grades_sum / len(students_with_avg)
print(f"\n overall avg: {overall_avg:.2f} \n")

### 1.3

top_student = reduce(
    lambda best, current: current
    if current["avg_grade"] > best["avg_grade"]
    else best,
    students_with_avg,
)
print(
    f"top student: {top_student['name']} with avg {top_student['avg_grade']:.2f} \n"
)

### 2

users = [
   {"name": "Alice", "expenses": [100, 50, 75, 200]},
   {"name": "Bob", "expenses": [50, 75, 80, 100]},
   {"name": "Charlie", "expenses": [200, 300, 50, 150]},
   {"name": "David", "expenses": [100, 200, 300, 400]},

# ... (другие пользователи)

]

total_expenses_users = list(
    map(
        lambda u: {
            "name" : u["name"],
            "total_expenses" : reduce(lambda a, b: a + b, u["expenses"], 0), 
        }, 
        users,
    )
)

filtered_users = list(
    filter(lambda u: u["total_expenses"] > 400, total_expenses_users)
)

total_filtered_expenses = reduce(
    lambda acc, u: acc + u["total_expenses"], filtered_users, 0
)

for user in total_expenses_users:
    print(f"total expenses of {user['name']}: {user['total_expenses']}")

print("\n")

for user in filtered_users:
    print(f"filtered users with total expenses of {user['name']}: {user['total_expenses']}")

print(f"\n overall users' expenses: {total_filtered_expenses} \n")

### 3


orders = [
   {"order_id": 1, "customer_id": 101, "amount": 150.0},
   {"order_id": 2, "customer_id": 102, "amount": 200.0},
   {"order_id": 3, "customer_id": 101, "amount": 75.0},
   {"order_id": 4, "customer_id": 103, "amount": 100.0},
   {"order_id": 5, "customer_id": 101, "amount": 50.0},

# ... (далее по списку)

]

example_target_id = 101

customer_orders = list(
    filter(lambda order: order["customer_id"] == example_target_id, orders)
)

amounts = list(map(lambda order: order["amount"], customer_orders))
total_spent = reduce(lambda a, b: a + b, amounts, 0.0)

avg_order_value = ((total_spent / len(customer_orders)) if customer_orders else 0.0)

print(f"orders of client with id {example_target_id}: {customer_orders}")
print(f"amount of orders: {len(customer_orders)}")
print(f"total orders sum: {total_spent:.2f}")
print(f"avg value of an order: {avg_order_value:.2f}")