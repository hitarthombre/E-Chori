def fibonacci(n):
    if n <= 1:
        return n
    else:
        return fibonacci(n - 1) + fibonacci(n - 2)

def fibonacci_series(count):
    series = []
    for i in range(count):
        series.append(fibonacci(i))
    return series

n = int(input("Enter number of terms: "))
print("Fibonacci Series:", fibonacci_series(n))
