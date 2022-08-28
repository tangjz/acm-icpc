class Solution {
public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        const int maxd = 6, maxm = 1 << maxd | 1, maxs = 46656; // pow(6, 6)
        static int tr[maxd + 1][maxd + 1], lbt[maxm] = {}, pw[maxd + 1] = {};
        static int st = 0, tim[maxs + 1] = {}, pos[maxs + 1][maxd + 1];
        memset(tr, 0, sizeof tr);
        for(auto &it: allowed) {
            int u = it[0] - 'A', v = it[1] - 'A', w = it[2] - 'A';
            tr[u][v] |= 1 << w;
        }
        if(!lbt[0]) {
            lbt[0] = -1;
            for(int i = 1; i < maxm; ++i)
                lbt[i] = i & 1 ? 0 : lbt[i >> 1] + 1;
            pw[0] = 1;
            for(int i = 1; i <= maxd; ++i)
                pw[i] = pw[i - 1] * maxd;
            for(int i = 0; i < maxs; ++i)
                for(int j = 0, tmp = i; j < maxd; ++j, tmp /= maxd)
                    pos[i][j] = tmp % maxd;
        }
        int n = bottom.size();
        static int que[2][maxs + 2], cur = 0, pre = 1;
        que[cur][0] = 1;
        for(int i = 0, &msk = que[cur][1] = 0; i < n; ++i)
            msk += (bottom[i] - 'A') * pw[i];
        for( ; n > 1; --n)
            for(int i = 0; i + 1 < n; ++i) {
                ++st;
                swap(cur, pre);
                que[cur][0] = 0;
                for(int j = 1; j <= que[pre][0]; ++j) {
                    int p = que[pre][j], q;
                    int u = pos[p][i], v = pos[p][i + 1];
                    for(int rem = tr[u][v], w; rem > 0; rem ^= 1 << w) {
                        w = lbt[rem];
                        q = p + (w - u) * pw[i] + (i + 2 < n ? 0 : -v * pw[i + 1]);
                        // printf("n %d i %d u %d v %d w %d: %d -> %d\n", n, i, u, v, w, p, q);
                        if(tim[q] != st) {
                            tim[q] = st;
                            que[cur][++que[cur][0]] = q;
                        }
                    }
                }
                if(!que[cur][0])
                    return 0;
            }
        return 1;
    }
};
