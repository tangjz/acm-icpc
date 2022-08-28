class Solution {
public:
    int getMaxGridHappiness(int m, int n, int introvertsCount, int extrovertsCount) {
        const int upp[3] = {introvertsCount, extrovertsCount};
        if(n > m)
            swap(n, m);
        // state: [pre[0..n-1], cur[0..n-1], c1, c2]
        int sz = 1 << n, sz2 = (upp[0] + 1) * (upp[1] + 1) << (n + n);
        vector<int> bits(sz), f(sz2, INT_MIN);
        for(int i = 0; i < (1 << n); ++i) {
            bits[i] = bits[i >> 1] + (i & 1);
            if(bits[i] <= upp[0] + upp[1])
                f[i << n] = 0;
        }
        for(int x = 0; x < m; ++x)
            for(int y = 0; y < n; ++y) {
                vector<int> g(sz2, INT_MIN);
                for(int cur = 0; cur < sz2; ++cur) {
                    if(f[cur] == INT_MIN)
                        continue;
                    const int cur2 = cur >> n, cur3 = cur2 >> n;
                    const int low[2] = {cur3 % (upp[0] + 1), cur3 / (upp[0] + 1)};
                    bool needPlace = (cur2 >> y) & 1;
                    bool canPlace = low[0] < upp[0] || low[1] < upp[1];
                    if(needPlace && !canPlace)
                        continue;
                    const int curVal = f[cur];
                    bool up = (cur >> y) & 1, lft = y > 0 && ((cur >> (y - 1)) & 1), rht = y + 1 < n && (cur2 >> (y + 1)) & 1;
                    int curCtr = up + lft + rht;
                    int canExtend = x + 1 < m && low[0] + low[1] + bits[cur2 & (sz - 1)] < upp[0] + upp[1];
                    for(int v = 0; v <= canExtend; ++v) {
                        int nxt = cur;
                        nxt ^= (up ^ needPlace) << y;
                        nxt ^= (needPlace ^ v) << (n + y);
                        if(!needPlace) {
                            int nxtVal = curVal;
                            g[nxt] = max(g[nxt], nxtVal);
                        } else {
                            int nxtCtr = curCtr + v;
                            if(low[0] < upp[0]) {
                                int nxt2 = nxt + (1 << (n + n));
                                int nxtVal = curVal + (4 - nxtCtr) * 30;
                                g[nxt2] = max(g[nxt2], nxtVal);
                            }
                            if(low[1] < upp[1]) {
                                int nxt2 = nxt + ((upp[0] + 1) << (n + n));
                                int nxtVal = curVal + (2 + nxtCtr) * 20;
                                g[nxt2] = max(g[nxt2], nxtVal);
                            }
                        }
                    }
                }
                f = move(g);
            }
        int ans = 0;
        for(int i = 0; i < sz2; ++i) {
            ans = max(ans, f[i]);
        }
        return ans;
    }
};
