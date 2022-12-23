class Solution {
public:
    int Leetcode(vector<string>& words) {
        static const char *goal = "helloleetcode";
        static const int maxc = 26, maxd = 7, maxs = 960, maxm = 8;
        static const int maxv = 1 << 21, BLEN = 3, BMSK = (1 << BLEN) - 1, INF = 0x3f3f3f3f;
        static int n = 0, idx[maxc + 1] = {}, upp[maxd] = {}, mp[maxv + 1] = {};
        static int tot = 0, seq[maxs + 1], tr[maxs + 1][maxs + 1] = {};
        static int lbt[1 << maxm | 1], f[maxm + 1][1 << maxm | 1];
        static pair<int, int> g[1 << maxm | 1];
        // (set, contrib) -> new_set
        // (i, msk) -> cost
        if(!idx[maxc]) {
            memset(idx, -1, sizeof idx);
            memset(mp, -1, sizeof mp);
            for(int i = 0; goal[i]; ++i) {
                int o = goal[i] - 'a';
                ++idx[o];
            }
            for(int i = 0; i < maxc; ++i)
                if(idx[i] >= 0) {
                    upp[n] = idx[i] + 1;
                    assert(upp[n] <= BMSK);
                    idx[i] = n++;
                }
            function<void(int, int)> dfs = [&](int dep, int msk) {
                if(dep == n) {
                    seq[tot] = msk;
                    mp[msk] = tot++;
                    return;
                }
                dfs(dep + 1, msk);
                for(int i = 1, adt = 1 << (BLEN * dep); i <= upp[dep]; ++i) {
                    dfs(dep + 1, msk += adt);
                }
            };
            dfs(0, 0);
            assert(tot > 0 && tot <= maxs && !seq[0]);
            for(int i = 0; i < tot; ++i)
                for(int j = 0; j < tot; ++j) {
                    if(i > j) {
                        tr[i][j] = tr[j][i];
                        continue;
                    }
                    bool skp = 0;
                    for(int k = 0, lft = seq[i], rht = seq[j]; !skp && k < n; ++k, lft >>= BLEN, rht >>= BLEN) {
                        int adt = (lft & BMSK) + (rht & BMSK);
                        skp |= adt > upp[k];
                    }
                    tr[i][j] = skp ? -1 : mp[seq[i] + seq[j]];
                }
            lbt[0] = -1;
            for(int i = 1; i < (1 << maxm); ++i)
                lbt[i] = i & 1 ? 0 : lbt[i >> 1] + 1;
            for(int m = 1; m <= maxm; ++m) {
                f[m][0] = 0;
                int all = (1 << m) - 1;
                for(int i = 1; i <= all; ++i) {
                    f[m][i] = INT_MAX;
                    int cL = 0, cR = __builtin_popcount(i);
                    for(int j = 0; j < m; ++j) {
                        if(!((i >> j) & 1))
                            continue;
                        --cR;
                        f[m][i] = min(f[m][i], f[m][i ^ (1 << j)] + (j - cL) * (m - 1 - j - cR));
                        ++cL;
                    }
                }
            }
        }
        // (i, msk) -> (contrib, cost)
        static int dp[maxs + 1];
        memset(dp, 0x3f, tot * sizeof(int));
        dp[0] = 0;
        for(auto &word: words) {
            int m = word.size(), all = (1 << m) - 1, sz = 0;
            static int cur[maxd] = {};
            for(int i = 1; i <= all; ++i) {
                bool skp = 0;
                int msk = 0;
                for(int j = 0; j < m; ++j) {
                    if(!((i >> j) & 1))
                        continue;
                    int v = word[j] - 'a';
                    v = idx[v];
                    if(v == -1 || (++cur[v]) > upp[v]) {
                        skp = 1;
                    } else {
                        msk += 1 << (BLEN * v);
                    }
                }
                if(!skp) {
                    g[sz++] = {mp[msk], f[m][i]};
                }
                for(int j = 0; j < m; ++j) {
                    if(!((i >> j) & 1))
                        continue;
                    int v = word[j] - 'a';
                    v = idx[v];
                    if(v != -1)
                        --cur[v];
                }
            }
            for(int i = tot - 1; i >= 0; --i) {
                if(dp[i] == INF)
                    continue;
                for(int j = 0; j < sz; ++j) {
                    int k = tr[i][g[j].first];
                    if(k == -1)
                        continue;
                    dp[k] = min(dp[k], dp[i] + g[j].second);
                }
            }
        }
        return dp[tot - 1] < INF ? dp[tot - 1] : -1;
    }
};
