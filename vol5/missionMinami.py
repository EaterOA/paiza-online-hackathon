x, y = input().split()
x, y = int(x), int(y)
bombs = [0]*x
for _ in range(y):
    for i, b in enumerate(input().split()):
        if b == "1":
            bombs[i] += 1
for i in range(y, 0, -1):
    print(" ".join("1" if b == i else "0" for b in bombs))
    bombs = [b-1 if b == i else b for b in bombs]
