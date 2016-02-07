# coding: utf-8

n = int(input())
cells = [int(i) for i in input().split()]
goal = [None] * n
goal[0] = False
goal[-1] = True

def jump(cur, seen):
    if cur < 0 or cur >= n:
        return False
    if goal[cur] != None:
        return goal[cur]
    if cur in seen:
        return False
    seen.add(cur)
    goal[cur] = jump(cur + cells[cur], seen)
    return goal[cur]

m = int(input())
for _ in range(m):
    d = int(input())
    print("Yes" if jump(d, set()) else "No")
