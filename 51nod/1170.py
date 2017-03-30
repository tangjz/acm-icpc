p, sz, pp, pw = 0, 0, 0, []
s, f, g, c = [], [], [], []

def mod_inv(x, m) :
    y, u, v = m, 1, 0
    while y != 0 :
        r = x // y
        x, y = y, x - y * r
        u, v = v, u - v * r
    assert x == 1
    return u % m

def poly_mul(f, g, h) :
    for i in range(sz) :
        f[i], h[i] = 0, f[i]
    for i in range(sz) :
        if not g[i] :
            continue
        for j in range(sz - i) :
            if h[j] :
                f[i + j] += g[i] * h[j]
    for i in range(sz) :
        f[i] %= pw[sz - i]

def poly_val(f, x, g, h) :
    g[0], h[0] = 0, 1
    for i in range(1, sz) :
        g[i], h[i] = 0, h[i - 1] * x % pp
    for i in range(sz) :
        if not f[i] :
            continue
        for j in range(i + 1) :
            if not c[i][j] :
                continue
            val = f[i] * h[i - j] % pw[sz - j]
            if val :
                g[j] += val * c[i][j]
    for i in range(sz) :
        g[i] %= pw[sz - i]

def mod_fact(n) :
    tmp, dig = n, []
    while tmp > 0 :
        dig.append(tmp % p)
        tmp = tmp // p
    Len = len(dig)
    ret, val = [1, 0], 0
    f[0] = 1
    for i in range(1, sz) :
        f[i] = 0
    for i in range(Len - 1, -1, -1) :
        ret[0] = ret[0] * f[0] % pp
        ret[1] = ret[1] + val
        val = val * p
        last = val
        for j in range(dig[i]) :
            val = val + 1
            ret[0] = ret[0] * val % pp
        # print("%d : %d * %d ^ %d (mod %d)" % (val, ret[0], p, ret[1], pp))
        if i == 0 :
            continue
        if last > 0 :
            if p == 2 :
                poly_val(f, last, g[0], g[1])
                poly_mul(f, g[0], g[1])
            else : # p == 5
                poly_val(f, last, g[0], g[2])
                poly_mul(g[0], f, g[2])
                poly_val(g[0], last << 1, g[1], g[2])
                poly_mul(g[1], g[0], g[2])
                poly_val(g[1], last, g[0], g[2])
                poly_mul(f, g[0], g[2])
        if dig[i] > 0 :
            poly_val(s[dig[i]], last * p, g[0], g[1])
            poly_mul(f, g[0], g[1])
    return ret

def init(pr, ex) :
    global p, sz, pp, pw, s, c
    p, sz, pp, pw = pr, ex, 1, [1]
    for i in range(sz) :
        pp *= p
        pw.append(pp)
    s[1][0] = 1
    for i in range(1, sz) :
        s[1][i] = 0
    for i in range(1, p) :
        for j in range(sz - 1, -1, -1) :
            s[1][j] = s[1][j] * i
            if j > 0 :
                s[1][j] = s[1][j] + s[1][j - 1]
            s[1][j] %= pw[sz - j]
    for i in range(2, p) :
        poly_val(s[1], (i - 1) * p, s[i], g[0])
        poly_mul(s[i], s[i - 1], g[0])
    for i in range(sz) :
        c[i][0] = c[i][i] = 1
        for j in range(1, i) :
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % pw[sz - j]

ans, mod = 0, 1
def solve(n, m) :
    ret, tmp = mod_fact(m), mod_fact(n - m)
    tmp[0] = tmp[0] * ret[0] % pp
    tmp[1] = tmp[1] + ret[1]
    ret = mod_fact(n)
    ret[0] = ret[0] * mod_inv(tmp[0], pp) % pp
    ret[1] = ret[1] - tmp[1]
    val = 0
    if ret[1] < sz :
        val = ret[0]
        for i in range(ret[1]) :
            val = val * p
    global ans, mod
    val = mod_inv(mod, pp) * (val - ans) % pp
    ans = val * mod + ans
    mod = mod * pp

if __name__ == "__main__" :
    n = int(input())
    m = int(input())
    k = int(input())
    # global f, g, s, c
    f = [0 for i in range(k)]
    g = [[0 for j in range(k)] for i in range(3)]
    s = [[0 for j in range(k)] for i in range(5)]
    c = [[0 for j in range(i + 1)] for i in range(k)]
    init(2, k)
    solve(n, m)
    init(5, k)
    solve(n, m)
    print(ans)
