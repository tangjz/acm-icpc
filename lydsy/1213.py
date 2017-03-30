import math
m, n = [int(input()) for i in range(2)]
if n == 0 :
    x = 0
else :
    x = 10 ** int(math.log10(n) / m)
    while True :
        last, x = x, int(x - x / m + n / (m * x ** (m - 1)))
        if last == x :
            break
    while x ** m > n :
        x -= 1
    while (x + 1) ** m <= n :
        x += 1
print x
