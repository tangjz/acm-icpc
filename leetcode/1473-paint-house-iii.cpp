class Solution {
public:
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int lim) {
        // dp[i][las][cnt]
        vector<vector<int> > f(n + 1, vector<int>(lim + 1, INT_MAX));
        f[0][0] = 0;
        for(int i = 0; i < m; ++i) {
            int L = 1, R = n;
            if(houses[i] > 0)
                L = R = houses[i];
            vector<vector<int> > g(n + 1, vector<int>(lim + 1, INT_MAX));
            for(int j = 0; j <= n; ++j)
                for(int k = 0; k <= lim; ++k) {
                    if(f[j][k] == INT_MAX)
                        continue;
                    for(int jj = L; jj <= R; ++jj) {
                        int kk = k + (j != jj);
                        if(kk > lim)
                            continue;
                        g[jj][kk] = min(g[jj][kk], f[j][k] + (houses[i] > 0 ? 0 : cost[i][jj - 1]));
                    }
                }
            f = move(g);
        }
        int ans = INT_MAX;
        for(int i = 0; i <= n; ++i)
            ans = min(ans, f[i][lim]);
        return ans < INT_MAX ? ans : -1;
    }
};
