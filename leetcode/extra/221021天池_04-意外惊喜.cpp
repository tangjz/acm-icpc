class Solution {
public:
    int brilliantSurprise(vector<vector<int>>& present, int limit) {
        int n = present.size();
        vector<int> tot(n);
        vector<vector<pair<int, int> > > seg(1);
        vector<vector<int> > dp(1, vector<int>(limit + 1));
        for(int i = 0; i < n; ++i) {
            for(int x: present[i])
                tot[i] += x;
            if(i > 0)
                seg[0].push_back({0, i - 1});
            if(i + 1 < n)
                seg[0].push_back({i + 1, n - 1});
        }
        int ans = 0;
        function<void(int, int, int)> solve = [&](int dep, int L, int R) {
            if(L == R) {
                int sz = present[L].size(), adt = 0;
                ans = max(ans, dp[dep][limit]);
                for(int i = 1; i <= sz && i <= limit; ++i) {
                    adt += present[L][i - 1];
                    ans = max(ans, adt + dp[dep][limit - i]);
                }
                return;
            }
            int M = (L + R) >> 1;
            for(auto &[pL, pR]: {make_pair(L, M), make_pair(M + 1, R)}) {
                if(seg.size() == dep + 1) {
                    seg.push_back({});
                    dp.push_back(vector<int>(limit + 1));
                }
                seg[dep + 1].clear();
                dp[dep + 1] = dp[dep];
                for(auto &[qL, qR]: seg[dep]) {
                    if(qL <= pL && pR <= qR) {
                        int u = qL ? qL - 1 : qR + 1, sz = present[u].size();
                        for(int i = limit; i >= sz; --i)
                            dp[dep + 1][i] = max(dp[dep + 1][i], dp[dep + 1][i - sz] + tot[u]);
                        continue;
                    }
                    if(qL <= pR || pL <= qR) {
                        seg[dep + 1].push_back({qL, qR});
                    }
                }
                solve(dep + 1, pL, pR);
            }
        };
        solve(0, 0, n - 1);
        return ans;
    }
};
