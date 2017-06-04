n, m = map(int, input().split(" "))
a = list(map(int, input().split(" ")))
b = list(map(int, input().split(" ")))
Log = [0] * (1 << max(n, m))
for i in range(max(n, m)) :
    Log[1 << i] = i
c = [1] * (1 << n)
for i in range(1, 1 << n) :
    msk = i & -i
    lbt = Log[msk]
    c[i] = c[i ^ msk] * a[lbt]
c.sort()
d = [1] * (1 << m)
for i in range(1, 1 << m) :
    msk = i & -i
    lbt = Log[msk]
    d[i] = d[i ^ msk] * b[lbt]
d.sort()
ans = 0
i, j = 1, 1
while i < (1 << n) and j < (1 << m) :
    if c[i] == d[j] :
        ans = c[i]
        break
    if c[i] < d[j] :
        i += 1
    else :
        j += 1
if ans == 0 :
    print("N")
    exit(0)
for i in range(1, 1 << n) :
    msk = i & -i
    lbt = Log[msk]
    c[i] = c[i ^ msk] * a[lbt]
    if c[i] == ans :
        ares = []
        for j in range(n) :
            if ((i >> j) & 1) == 1 :
                ares.append(a[j])
        break
for i in range(1, 1 << m) :
    msk = i & -i
    lbt = Log[msk]
    d[i] = d[i ^ msk] * b[lbt]
    if d[i] == ans :
        bres = []
        for j in range(m) :
            if ((i >> j) & 1) == 1 :
                bres.append(b[j])
        break
print("Y")
print("%d %d" % (len(ares), len(bres)))
for i in range(len(ares)) :
    print(ares[i], end = " \n"[i == len(ares) - 1])
for i in range(len(bres)) :
    print(bres[i], end = " \n"[i == len(bres) - 1])
