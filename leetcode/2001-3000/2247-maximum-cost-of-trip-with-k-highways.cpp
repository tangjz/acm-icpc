class Solution {
public:
    int maximumCost(int n, vector<vector<int>>& highways, int k) {
        if((++k) > n)
            return -1;
        int ans = -1, m = 1 << n;
        vector<int> bits(m), msk(n);
        vector<vector<int> > dp(n, vector<int>(m, -1)), e(n, vector<int>(n, -1));
        for(auto &it: highways) {
            int u = it[0], v = it[1], w = it[2];
            msk[u] |= 1 << v;
            msk[v] |= 1 << u;
            e[u][v] = max(e[u][v], w);
            e[v][u] = max(e[v][u], w);
        }
        for(int i = 0; i < n; ++i)
            dp[i][1 << i] = 0;
        for(int i = 1; i < m; ++i) {
            bits[i] = bits[i >> 1] + (i & 1);
            if(bits[i] <= 1 || bits[i] > k)
                continue;
            for(int u = 0; u < n; ++u) {
                if(!((i >> u) & 1))
                    continue;
                for(int v = 0; v < n; ++v) {
                    if(!(((i & msk[u]) >> v) & 1) || dp[v][i ^ (1 << u)] == -1)
                        continue;
                    dp[u][i] = max(dp[u][i], dp[v][i ^ (1 << u)] + e[u][v]);
                }
                if(bits[i] == k)
                    ans = max(ans, dp[u][i]);
            }
        }
        return ans;
    }
};
