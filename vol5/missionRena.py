x, y, N = [int(n) for n in input().split()]

sheet = []
locked = []
for _ in range(y):
    sheet.append([int(n) for n in input().split()])
    locked.append([False] * x)

sum = 0 
for _ in range(N):
    x1, y1, x2, y2 = [int(n) for n in input().split()]
    for x in range(x1-1, x2):
        for y in range(y1-1, y2):
            if not locked[y][x]:
                sum += sheet[y][x]
                locked[y][x] = True
                
print(sum)
