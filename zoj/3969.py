T = int(input())
query = []
for idx in range(T) :
        x = int(input())
        query.append([idx, x])
query.sort(key = lambda a : a[1])
limit, mod = query[T - 1][1] + (query[T - 1][1] & 1), 10 ** 9 + 7
seq = [0, 1, 2]
dif = [0, 1, 2]
vis = {}
vis[1] = [2, 1]
for i in range(3, 1001) :
        val = seq[-1] << 1 if (i & 1) == 1 else seq[-1] + dif[-1]
        if val - seq[-1] > limit :
                break # now, n is even
        for j in range(1, i) :
                dt = val - seq[-j]
                if dt > limit :
                        break
                vis[dt] = [i, i - j]
        seq.append(val)
        mex = dif[-1]
        while mex in vis :
                mex += 1
        dif.append(mex)
assert (len(seq) & 1) == 1
que = []
for item in vis :
        if item >= dif[-1] :
                que.append(item)
que.sort()
que.append(limit + 1)
pos = len(seq) - 1
last, rem = dif[-1] - 1, (limit - pos) >> 1
val, ans, idx = seq[-1] % mod, 0, 0
for i in range(1, pos + 1) :
        ans = (ans + seq[i]) % mod
        while idx < T and query[idx][1] == i :
                query[idx][1] = ans
                idx += 1
for cur in que :
        if last + 1 < cur :
                width = cur - last - 1
                if width > rem :
                        width = rem
                nxtpos = pos + (width << 1)
                while idx < T and query[idx][1] <= nxtpos :
                        wid = (query[idx][1] - pos) >> 1
                        if wid > 0 :
                                ww, dt = wid % mod, last % mod
                                coeff = pow(2, wid % (mod - 1), mod)
                                coeff2 = ((coeff << 2) - 4) % mod
                                ans = (ans + coeff2 * (val + dt + 2) - ww * (3 * dt + 4) - ww * (ww + 1) // 2 * 3) % mod
                                val = (coeff * (val + dt + 2) - (ww + dt + 2)) % mod
                                rem -= wid
                                pos += wid << 1
                                last += wid
                        query[idx][1] = ans if query[idx][1] == pos else (ans + (val << 1)) % mod
                        idx += 1
                if pos < nxtpos :
                        wid = (nxtpos - pos) >> 1
                        ww, dt = wid % mod, last % mod
                        coeff = pow(2, wid % (mod - 1), mod)
                        coeff2 = ((coeff << 2) - 4) % mod
                        ans = (ans + coeff2 * (val + dt + 2) - ww * (3 * dt + 4) - ww * (ww + 1) // 2 * 3) % mod
                        val = (coeff * (val + dt + 2) - (ww + dt + 2)) % mod
                        rem -= wid
                        pos += wid << 1
                if rem == 0 :
                        break
        last = cur
query.sort(key = lambda a : a[0])
for i in range(T) :
        print(query[i][1])
