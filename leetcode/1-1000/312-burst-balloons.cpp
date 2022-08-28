class Solution {
public:
    int maxCoins(vector<int>& nums) {
        vector<int> vals;
        vals.push_back(1);
        vals.insert(vals.end(), nums.begin(), nums.end());
        vals.push_back(1);
        int n = (int)vals.size();
        vector<vector<int> > dp(n, vector<int>(n, 0));
        for(int len = 3; len <= n; ++len)
            for(int L = 0, R = len - 1; R < n; ++L, ++R) {
                int com = vals[L] * vals[R];
                for(int M = L + 1; M < R; ++M)
                    dp[L][R] = max(dp[L][R], dp[L][M] + dp[M][R] + com * vals[M]);
            }
        return dp[0][n - 1];
    }
};
