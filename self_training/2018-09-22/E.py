import math
a = []
for n in range(2001) :
    if n < 5 :
        val = ((n - 1) * (n - 2) // 2) ** 2
    else :
        val = (n - 1) * (2 * (n ** 3 - 2 * n ** 2 + n + 1) * a[n - 1] + (n - 2) * ((n ** 2 - 2 * n + 2) * (n + 1) * a[n - 2] + (2 * n ** 2 - 6 * n + 1) * n * a[n - 3] + (n - 3) * (a[n - 4] * (n ** 3 - 5 * n ** 2 + 3) - (n - 4) * (n - 1) * (n + 1) * a[n - 5]))) // (2 * n * (n - 2))
    a += [val]
for case in range(int(raw_input())) :
    n, p = map(int, raw_input().split(" "))
    print(a[n] % p * (math.factorial(n) % p) % p)

