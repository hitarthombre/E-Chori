students = {}

for i in range(1, 4):
    name = input(f"Enter name of student {i}: ")
    students[name] = {}
    for subject in ["Maths", "Science", "English", "History", "Computer"]:
        mark = int(input(f"Enter marks in {subject} for {name}: "))
        students[name][subject] = mark

print("\nStudent Grades:")
for name, subjects in students.items():
    total = sum(subjects.values())
    percentage = total / 5
    if percentage >= 90:
        grade = "A"
    elif percentage >= 80:
        grade = "B"
    elif percentage >= 70:
        grade = "C"
    elif percentage >= 60:
        grade = "D"
    else:
        grade = "F"
    print(f"{name}: {percentage:.2f}% -> Grade {grade}")
