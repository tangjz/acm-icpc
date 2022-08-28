class Solution {
public:
    int numOfArrays(int n, int m, int k) {
        typedef long long LL;
        const int maxn = 51, maxm = 101, mod = (int)1e9 + 7;
        auto mod_inc = [&](int &x, int y) {
            (x += y) >= mod && (x -= mod);
        };
        static int dp[2][maxn][maxm], pre = 0, cur = 1;
        auto arr_clear = [&](int idx) {
            for(int i = 0; i <= k; ++i)
                memset(dp[idx][i], 0, (m + 1) * sizeof(int));
        };
        arr_clear(cur);
        dp[cur][0][0] = 1;
        for(int i = 1; i <= n; ++i) {
            swap(pre, cur);
            arr_clear(cur);
            for(int u = 0; u <= i && u <= k; ++u) {
                int sum = 0;
                for(int v = u; v <= m; ++v) {
                    mod_inc(sum, dp[pre][u][v]);
                    if(u + 1 <= k && v + 1 <= m)
                        mod_inc(dp[cur][u + 1][v + 1], sum);
                    mod_inc(dp[cur][u][v], (LL)v * dp[pre][u][v] % mod);
                }
            }
        }
        int ans = 0;
        for(int i = 0; i <= m; ++i)
            mod_inc(ans, dp[cur][k][i]);
        return ans;
    }
};
