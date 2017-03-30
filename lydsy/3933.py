def a(i) :
    return (209 * (1234 ** (i % 3388)) + 3181) % 3389
n, t, m = [int(raw_input()) for i in range(3)]
ans, binom, val = 0, 1, 1
for i in range(n - m + 1) :
    ans += binom * val * a(m + i)
    binom = binom * (m + i + 1) // (i + 1)
    val *= t
print ans
