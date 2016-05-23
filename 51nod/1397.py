t = int(input())
for case in range(t) :
    n1, n2, m, d = map(int, input().split(" "))
    if n1 > n2 :
        n1, n2 = n2, n1
    if m == n1 :
        print(n1 * n2)
        continue
    elif d + d > m :
        print(-1)
        continue
    else :
        print(m * m + (n1 - m) * (n2 - m) - min((d - (n1 - m)) * (m - d - (n2 - m)), (d - (n2 - m)) * (m - d - (n1 - m))))
