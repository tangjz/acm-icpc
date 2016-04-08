t = int(raw_input())
for test in range(t) :
    n, p = map(int, raw_input().split())
    tmp = n + 1
    ans = 1
    while n != 0 :
        ans = ans * (n % p + 1)
        n = n / p
    print tmp - ans
