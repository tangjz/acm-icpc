maxn = 51
f = [[1]]
ans = [0 for i in range(maxn)]
for i in range(1, maxn) :
    g = [0]
    for j in range(1, i + 1) :
        val = f[i - 1][j - 1] * j
        if j < i :
            val += f[i - 1][j] * j
        ans[i] += val
        g.append(val)
    f.append(g)
t = int(raw_input())
for test in range(t) :
    n = int(raw_input())
    print ans[n]
