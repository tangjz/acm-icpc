import random, math

times = 20

def gcd(a, b) :
    if a < b :
        a, b = b, a
    r = a % b
    while r > 0 :
        a, b, r = b, r, b % r
    return b
def isPrime(x) :
    if x < 2 :
        return False
    i = 2
    while i * i <= x :
        if x % i == 0 :
            return False
        i += 1
    return True
def getRoot(x, k) :
    y = 10 ** math.ceil(len(str(x)) / k)
    while not (y ** k <= x and (y + 1) ** k > x) :
        y = ((k - 1) * y + x // y ** (k - 1)) // k
#    print("getRoot", x, k, y)
    return y
def isPower(x, k) :
    return getRoot(x, k) ** k == x

T = int(input())
for case in range(T) :
    n, pw = map(int, input().split(" "))
    ex = 0
    while pw % 2 == 0 :
        pw, ex = pw >> 1, ex + 1
    pr = []
    if n % 2 == 0 :
        ctr = 0
        while n % 2 == 0 :
            n, ctr = n >> 1, ctr + 1
        pr += [(2, ctr)]
    if n % 3 == 0 :
        ctr = 0
        while n % 3 == 0 :
            n, ctr = n // 3, ctr + 1
        pr += [(3, ctr)]
    if n % 5 == 0 :
        ctr = 0
        while n % 5 == 0 :
            n, ctr = n // 5, ctr + 1
        pr += [(5, ctr)]
    if n % 7 == 0 :
        ctr = 0
        while n % 7 == 0 :
            n, ctr = n // 7, ctr + 1
        pr += [(7, ctr)]
    que = [n]
#    Case = 0
    while len(que) > 0 :
        m = que[-1]
        que = que[ : -1]
        if m == 1 :
            continue
        chk = False
        for tim in range(times) :
            x = pow(random.randint(2, m - 2), pw, m)
            for i in range(ex) :
                if x <= 1 :
                    break
                if x > 2 :
                    r = gcd(x - 1, m)
                    if r > 1 :
                        chk = True
                        que += [r, m // r]
                        break
                x = x * x % m
            if chk :
                break
        if not chk :
            r = m
            i, lim = 2, len(str(r))
            while i <= lim :
                if isPrime(i) :
                    while isPower(r, i) :
                        r = getRoot(r, i)
                        lim = len(str(r))
                i += 1
#            print("r", r)
            ctr = 0
            while m % r == 0 :
                m, ctr = m // r, ctr + 1
            for i in range(len(que)) :
                while que[i] % r == 0 :
#                    print("div que[%d]" % i, r)
                    que[i], ctr = que[i] // r, ctr + 1
            pr += [(r, ctr)]
#        Case += 1
#        print("#%d:" % Case, que)
    pr.sort()
    print(len(pr))
    for (p, e) in pr :
        print(p, e)
