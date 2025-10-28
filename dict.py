d = {"a": 1, "b": 2, "c": 3}
print("Original Dictionary:", d)

d.clear()
print("After clear():", d)

d = {"a": 1, "b": 2, "c": 3}
x = d.copy()
print("After copy():", x)

d = {"a": 1, "b": 2, "c": 3}
x = {}.fromkeys(["x", "y", "z"], 0)
print("After fromkeys():", x)

d = {"a": 1, "b": 2, "c": 3}
print("get('b'):", d.get("b"))

print("items():", d.items())

print("keys():", d.keys())

print("values():", d.values())

print("pop('b'):", d.pop("b"))
print("After pop():", d)

print("popitem():", d.popitem())
print("After popitem():", d)

d.update({"d": 4})
print("After update():", d)

print("setdefault('e', 5):", d.setdefault("e", 5))
print("After setdefault():", d)

print("get('f', 'Not Found'):", d.get("f", "Not Found"))
