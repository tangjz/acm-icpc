def mod_inv(x, m) :
    y, u, v = m, 1, 0
    while y != 0 :
        r = x // y
        x, y = y, x - y * r
        u, v = v, u - v * r
    assert x == 1
    return u % m
n, m = map(int, raw_input().split(" "))
if n < m :
    n, m = m, n
if n - m < m :
    m = n - m
fz, fm, c2, c5, mod = 1, 1, 0, 0, 10 ** 50
for i in range(m) :
    j = n - i
    while (j & 1) == 0 :
        j, c2 = j >> 1, c2 + 1
    while j % 5 == 0 :
        j, c5 = j // 5, c5 + 1
    fz = fz * j % mod
    j = i + 1
    while (j & 1) == 0 :
        j, c2 = j >> 1, c2 - 1
    while j % 5 == 0 :
        j, c5 = j // 5, c5 - 1
    fm = fm * j % mod
print fz * mod_inv(fm, mod) % mod * pow(2, c2, mod) % mod * pow(5, c5, mod) % mod
