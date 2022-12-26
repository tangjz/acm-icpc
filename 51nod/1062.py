import heapq, bisect
maxn = 10 ** 5
f = {0 : 0, 1 : 1}
def F(x) :
    if x in f :
        return f[x]
    if (x & 1) == 1 :
        f[x] = F(x >> 1) + F((x + 1) >> 1)
    else :
        f[x] = F(x >> 1)
    return f[x]
idx, val = [0], [F(0)]
que = [1]
while len(que) > 0 :
    u = heapq.heappop(que)
    fu = F(u)
    if val[-1] >= fu :
        continue
    idx += [u]
    val += [fu]
    v = (u << 1) - 1
    if v <= maxn :
        heapq.heappush(que, v)
    v = (u << 2) - 1
    if v <= maxn :
        heapq.heappush(que, v)
T = int(input())
for case in range(T) :
    n = int(input())
    i = bisect.bisect_right(idx, n)
    print(val[i - 1])
