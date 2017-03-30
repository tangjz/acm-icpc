def dfs(dep, val, mu) :
    if dep == len(pr) :
        global ans
        ans += mu * (m // val) ** n
        return
    dfs(dep + 1, val, mu)
    dfs(dep + 1, val * pr[dep], -mu)

if __name__ == "__main__" :
    n, m = map(int, raw_input().split())
    pr, i, tmp = [], 2, m
    while i * i <= tmp :
        cnt = 0
        while tmp % i == 0 :
            cnt, tmp = cnt + 1, tmp // i
        if cnt > 0 :
            pr.append(i)
        i += 1
    if tmp > 1 :
        pr.append(tmp)
    ans = 0
    dfs(0, 1, 1)
    print ans
