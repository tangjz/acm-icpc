import decimal, fractions, math
decimal.getcontext().prec = 1000
pi = decimal.Decimal(math.pi)
def solve(d, xL, yL, xR, yR, bound) :
    sq = decimal.Decimal(d).sqrt()
    xM, yM = xL + xR, yL + yR
    seq = [(int(pi), 0)]
    cE = pi - int(pi)
    assert int(pi) <= bound
    while yM <= bound :
        if xM * xM <= yM * yM * d :
            L, R = 1, (bound - yL) // yR
            while L < R :
                M = (L + R + 1) >> 1
                xM = xL + M * xR
                yM = yL + M * yR
                if xM * xM <= yM * yM * d :
                    L = M
                else :
                    R = M - 1
            xL += L * xR
            yL += L * yR
            x, y = xL, yL
        else :
            L, R = 1, (bound - yR) // yL
            while L < R :
                M = (L + R + 1) >> 1
                xM = xR + M * xL
                yM = yR + M * yL
                if xM * xM > yM * yM * d :
                    L = M
                else :
                    R = M - 1
            xR += L * xL
            yR += L * yL
            x, y = xR, yR
        xM, yM = xL + xR, yL + yR
        i = 0
        while i < len(seq) :
            uA, uB = seq[i][0] + x, seq[i][1] - y
            if max(abs(uA), abs(uB)) <= bound :
                uE = abs(uA + uB * sq - pi)
                if uE < cE :
                    seq += [(uA, uB)]
                    cE = uE
            uA, uB = seq[i][0] - x, seq[i][1] + y
            if max(abs(uA), abs(uB)) <= bound :
                uE = abs(uA + uB * sq - pi)
                if uE < cE :
                    seq += [(uA, uB)]
                    cE = uE
            i += 1
        if len(seq) > 1 :
            seq = seq[-2 : ]
    cA, cB = seq[-1][0], seq[-1][1]
    print("%d: %d %d" % (d, cA, cB))
    return cA

rt = 0
ans = 0
for i in range(100) :
    if i == rt * rt :
        rt += 1
        continue
    res = solve(i, rt - 1, 1, rt, 1, 10 ** 13)
    ans += abs(res)
print(ans)
