t = int(raw_input())
for test in range(t) :
    n = int(raw_input())
    seq, L, R, vis = [], 0, 0, {}
    seq.append(n)
    R += 1
    vis[n] = 0
    while L < R :
        u = seq[L]
        if u > 1 :
            v = u >> 1
            if not v in vis :
                seq.append(v)
                R += 1
                vis[v] = 0
            if (u & 1) == 1 :
                v += 1
                if not v in vis :
                    seq.append(v)
                    R += 1
                    vis[v] = 0
        L += 1
    seq = sorted(seq)
    for it in seq :
        if it > 1 :
            vis[it] = vis[it >> 1]
            if (it & 1) == 1 :
                vis[it] += vis[(it >> 1) + 1]
        else :
            vis[it] = it
    print vis[n]
