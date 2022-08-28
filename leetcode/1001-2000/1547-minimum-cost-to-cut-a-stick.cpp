class Solution {
public:
    int minCost(int n, vector<int>& cuts) {
        int las = 0;
        vector<int> w;
        sort(cuts.begin(), cuts.end());
        cuts.insert(cuts.begin(), 0);
        cuts.push_back(n);
        int m = (int)cuts.size() - 1;
        vector<vector<int> > dp(m, vector<int>(m, INT_MAX));
        for(int i = 0; i < m; ++i)
            dp[i][i] = 0;
        for(int i = 2; i <= m; ++i)
            for(int L = 0, R = i - 1; R < m; ++L, ++R)
                for(int M = L; M < R; ++M)
                    dp[L][R] = min(dp[L][R], dp[L][M] + dp[M + 1][R] + cuts[R + 1] - cuts[L]);
        return dp[0][m - 1];
    }
};
