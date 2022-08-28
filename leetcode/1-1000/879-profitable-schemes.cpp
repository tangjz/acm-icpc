class Solution {
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        static const int mod = (int)1e9 + 7;
        auto modInc = [&](int &x, int y) {
            (x += y) >= mod && (x -= mod);
        };
        int m = group.size();
        vector<vector<int> > dp(n + 1, vector<int>(minProfit + 1));
        dp[0][0] = 1;
        for(int i = 0; i < m; ++i)
            for(int j = n - group[i]; j >= 0; --j)
                for(int k = 0; k <= minProfit; ++k)
                    modInc(dp[j + group[i]][min(k + profit[i], minProfit)], dp[j][k]);
        int ans = 0;
        for(int i = 0; i <= n; ++i)
            modInc(ans, dp[i][minProfit]);
        return ans;
    }
};
