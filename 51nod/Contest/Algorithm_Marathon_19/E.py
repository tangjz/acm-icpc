from decimal import *
def Ex(x, n) :
    ret, tmp, len = Decimal(1), Decimal(x), n
    while len > 0 :
        if (len & 1) == 1 :
            ret *= tmp
        len >>= 1
        if len > 0 :
            tmp *= tmp
    return ret

def f(n, m, p) :
    if p > Decimal(0.5) :
        r = (1 - p) / p
        tmp = Ex(r, n + m)
        return (1 - Ex(r, n)) / (1 - tmp)
    else :
        r = p / (1 - p)
        tmp = Ex(r, n + m)
        return (Ex(r, m) - tmp) / (1 - tmp)

if __name__ == "__main__" :
    getcontext().prec = 80
    t = int(input())
    for test in range(t) :
        n, m, x, p1, p2 = input().split(" ")
        n, m, x, p1, p2 = int(n), int(m), int(x), Decimal(p1), Decimal(p2)
        q1 = f(m, x, 1 - p1)
        q2 = f(n - x, 1, p2)
        q3 = f(m + x - 1, 1, 1 - p1)
        q4 = f(1, m + x - 1, p1)
        q5 = f(x, m, p1)
        ans = q5 + q1 * q2 * q4 / (1 - q2 * q3)
        print("%.10f" % float(ans))
