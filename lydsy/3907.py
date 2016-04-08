fact = []
def Binom(n, m) :
    return fact[n] / fact[m] / fact[n - m]
fact.append(1)
for i in range(1, 10001) :
    fact.append(fact[i - 1] * i)
n, m = map(int, raw_input().split())
print Binom(n + m, n) - Binom(n + m, n + 1)
