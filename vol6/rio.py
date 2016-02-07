# coding: utf-8
N = int(input())
water = coffee = 0.0
for _ in range(N):
    t, s = (int(n) for n in input().split())
    if t == 1:
        water += s
    elif t == 2:
        coffee += s
    elif t == 3:
        frac = s/(water+coffee)
        water *= (1-frac)
        coffee *= (1-frac)
        
print(int(coffee/(water+coffee) * 100))
