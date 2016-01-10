n = int(input())
subtotal = [0]*7
for i in range(n):
    subtotal[i%7] += int(input())
for t in subtotal:
    print(t)
