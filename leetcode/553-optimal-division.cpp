class Solution {
public:
    string optimalDivision(vector<int>& nums) {
        int n = nums.size();
        vector<vector<vector<pair<double, int> > > > dp(2, vector<vector<pair<double, int> > >(n, vector<pair<double, int> >(n)));
        for(int i = 0; i < n; ++i)
            dp[0][i][i] = dp[1][i][i] = {log(nums[i]), i};
        for(int len = 2; len <= n; ++len)
            for(int L = 0, R = len - 1; R < n; ++L, ++R) {
                dp[0][L][R] = {-1e100, L};
                dp[1][L][R] = {1e100, L};
                for(int M = L; M < R; ++M) {
                    dp[0][L][R] = max(dp[0][L][R], make_pair(dp[0][L][M].first - dp[1][M + 1][R].first, M));
                    dp[1][L][R] = min(dp[1][L][R], make_pair(dp[1][L][M].first - dp[0][M + 1][R].first, M));
                }
            }
        function<string(int, int, int)> gen = [&](int o, int L, int R) {
            if(L == R)
                return to_string(nums[L]);
            int M = dp[o][L][R].second;
            string lft = gen(o, L, M), rht = gen(!o, M + 1, R);
            if(M + 1 < R)
                rht = "(" + rht + ")";
            return lft + "/" + rht;
        };
        return gen(0, 0, n - 1);
    }
};
