n, m = map(int, raw_input().split(" "))
seq = []
for i in range(m) :
    u, v = map(int, raw_input().split(" "))
    seq += [(1 << (u - 1), 1 << (v - 1))]
ways = [0] * (m + 1)
def dfs(dep, cnt, lft, rht) :
    if dep == m :
        global ways
        ways[cnt] += 1
    else :
        dfs(dep + 1, cnt, lft, rht)
        if (not (lft & seq[dep][0])) and (not (rht & seq[dep][1])) :
            dfs(dep + 1, cnt + 1, lft | seq[dep][0], rht | seq[dep][1])
dfs(0, 0, 0, 0)
for i in range(1, m + 1, 2) :
    ways[i] = -ways[i]
for i in range(n + 1) :
    ans = 0
    for j in range(min(i, m) + 1) :
        if not ways[j] :
            continue
        ans += ways[j]
        if i < n :
            ways[j] = ways[j] * (n - i) ** 2 // (i - j + 1)
    print(ans)
