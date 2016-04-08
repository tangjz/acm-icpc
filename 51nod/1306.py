def bsearch(seq, val) :
    L, R = 0, len(seq) - 1
    while L < R :
        M = L + (R - L) // 2
        if seq[M] < val :
            L = M + 1
        else :
            R = M
    return L

maxk = 65
maxn = 10 ** 18 + 1

ans = [[], [], [], []]
for k in range(4, maxk) :
    ans.append([])
    for m in range(0, maxn) :
        cnt = 0
        now = 1
        for i in range(1, k + 1) :
            tmp1 = m + 1 - i
            if tmp1 == 0 :
                break
            tmp2 = i
            now = now * tmp1 // tmp2
            cnt = cnt + now
            if cnt >= maxn :
                break
        if cnt >= maxn :
            ans[k].append(maxn)
            break
        ans[k].append(cnt)

test = int(input())
for case in range(test) :
    n, m = (int(x) for x in input().split(' '))
    if m == 1 :
        print(n)
    elif m == 2 :
        ret = int(((n * 8 + 1) ** 0.5 - 1) / 2)
        if ret * (ret + 1) / 2 < n :
            ret = ret + 1
        print(ret)
    elif m == 3 :
        ret = int((n * 6) ** (1 / 3) + 0.5)
        if ret * (ret * ret + 5) / 6 < n :
            ret = ret + 1
        print(ret)
    else :
        print(bsearch(ans[m], n))
