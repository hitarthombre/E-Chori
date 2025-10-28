def calculator():
    print("\n===== Calculator Menu =====")
    print("1. Addition")
    print("2. Subtraction")
    print("3. Multiplication")
    print("4. Division")
    print("5. Palindrome Check")
    print("6. Mean of numbers")
    print("7. Leap Year Check")
    print("8. Simple Interest")
    print("9. Profit or Loss")
    print("10. Area Calculation")
    print("0. Exit")

    while True:
        choice = int(input("\nEnter your choice: "))

        if choice == 0:
            print("Exiting Calculator. Goodbye!")
            break

        elif choice == 1:
            a, b = map(float, input("Enter two numbers: ").split())
            print("Result:", a + b)

        elif choice == 2:
            a, b = map(float, input("Enter two numbers: ").split())
            print("Result:", a - b)

        elif choice == 3:
            a, b = map(float, input("Enter two numbers: ").split())
            print("Result:", a * b)

        elif choice == 4:
            a, b = map(float, input("Enter two numbers: ").split())
            print("Result:", a / b if b != 0 else "Division by zero not allowed")

        elif choice == 5:
            s = input("Enter string/number: ")
            print("Palindrome" if s == s[::-1] else "Not Palindrome")

        elif choice == 6:
            nums = list(map(float, input("Enter numbers separated by space: ").split()))
            print("Mean:", sum(nums) / len(nums))

        elif choice == 7:
            year = int(input("Enter year: "))
            if (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0):
                print("Leap Year")
            else:
                print("Not a Leap Year")

        elif choice == 8:
            p, r, t = map(float, input("Enter Principal, Rate, Time: ").split())
            print("Simple Interest:", (p * r * t) / 100)

        elif choice == 9:
            cost, sell = map(float, input("Enter Cost Price and Selling Price: ").split())
            if sell > cost:
                print("Profit:", sell - cost)
            elif cost > sell:
                print("Loss:", cost - sell)
            else:
                print("No Profit No Loss")

        elif choice == 10:
            print("a. Square\nb. Rectangle\nc. Triangle")
            shape = input("Choose shape: ")

            if shape.lower() == 'a':
                side = float(input("Enter side: "))
                print("Area of Square:", side * side)

            elif shape.lower() == 'b':
                l, w = map(float, input("Enter length and width: ").split())
                print("Area of Rectangle:", l * w)

            elif shape.lower() == 'c':
                b, h = map(float, input("Enter base and height: ").split())
                print("Area of Triangle:", 0.5 * b * h)

        else:
            print("Invalid choice! Try again.")

calculator()
