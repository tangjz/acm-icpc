class Solution {
public:
    int minimumLines(vector<vector<int>>& p) {
        int n = p.size(), m = 1 << n;
        vector<int> dp(m, n);
        dp[0] = 0;
        vector<bool> vis(m);
        for(int i = 0; i < n; ++i) {
            vis[1 << i] = 1;
            for(int j = i + 1; j < n; ++j) {
                int ux = p[i][0] - p[j][0];
                int uy = p[i][1] - p[j][1];
                int msk = 0;
                for(int k = 0; k < n; ++k) {
                    int vx = p[i][0] - p[k][0];
                    int vy = p[i][1] - p[k][1];
                    if(ux * vy == uy * vx)
                        msk |= 1 << k;
                }
                vis[msk] = 1;
            }
        }
        for(int i = m - 1; i >= 0; --i) {
            if(!vis[i])
                continue;
            for(int j = i; j; j = (j - 1) & i)
                vis[i ^ j] = 1;
        }
        for(int i = 1; i < m; ++i)
            for(int j = i; j; j = (j - 1) & i)
                if(vis[j])
                    dp[i] = min(dp[i], dp[i ^ j] + 1);
        return dp.back();
    }
};
