import math
n = int(input())
x = 10 ** int(math.log10(n) // 2)
while not (x * x <= n and (x + 1) * (x + 1) > n) :
    x = int((x + n // x) // 2)
print(x)

