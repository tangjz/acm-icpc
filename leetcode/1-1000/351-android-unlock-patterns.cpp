class Solution {
public:
    int numberOfPatterns(int m, int n) {
        static const int maxd = 9, maxs = 1 << maxd | 1;
        static int ways[maxd + 2] = {}, bits[maxs], dp[maxd][maxs] = {};
        if(!ways[1]) {
            int tot = 0;
            bits[0] = 0;
            for(int i = 0; i < maxd; ++i)
                dp[i][1 << i] = 1;
            for(int i = 1; i < maxs; ++i) {
                bits[i] = bits[i >> 1] + (i & 1);
                for(int u = 0; u < maxd; ++u) {
                    if(!dp[u][i])
                        continue;
                    ways[bits[i]] += dp[u][i];
                    for(int v = 0; v < maxd; ++v) {
                        if((i >> v) & 1 || (gcd(abs(u / 3 - v / 3), abs(u % 3 - v % 3)) == 2 && !((i >> ((u + v) >> 1)) & 1)))
                            continue;
                        dp[v][i | 1 << v] += dp[u][i];
                    }
                }
            }
        }
        int ans = 0;
        for(int i = m; i <= n; ++i)
            ans += ways[i];
        return ans;
    }
};
