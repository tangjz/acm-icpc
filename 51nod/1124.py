t = int(input())
for tt in range(t) :
    n = int(input())
    if n == 1 :
        print(1)
        continue
    r, e = 1, 0
    while n > 0 :
        for i in range(n % 5) :
            r = r * (i + 1) % 5
        n = n // 5
        if n & 1 :
            r = 5 - r
        e = (e + n) & 3
    for i in range(e) :
        r = r * 3 % 5
    if r & 1 :
        r = r + 5
    print(r)
