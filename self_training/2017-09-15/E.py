from fractions import *
f = []
f.append([Fraction(0, 1), Fraction(1, 1)])
for i in range(1, 401) :
    g = [Fraction(0, 1), Fraction(1, 1)]
    for j in range(2, i + 2) :
        g.append(f[i - 1][j - 1] * Fraction(i, j))
        g[1] -= g[j]
    f.append(g)
t = int(input())
for test in range(t) :
    Case, n, m = map(int, input().split())
    print("%d %s" % (Case, f[n][m]))
