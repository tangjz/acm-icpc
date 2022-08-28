class Solution {
public:
    bool canCross(vector<int>& stones) {
        if(stones[1] != 1)
            return 0;
        int n = stones.size();
        vector<vector<bool> > dp(n, vector<bool>(n));
        dp[1][0] = 1;
        for(int i = 1; i < n; ++i)
            for(int j = i - 1, k = i + 1; k < n; ++k) {
                int dis = stones[k] - stones[i];
                for( ; j >= 0 && stones[i] - stones[j] < dis - 1; --j);
                dp[k][i] = (j >= 0 && dp[i][j] && stones[i] - stones[j] <= dis + 1) ||
                    (j >= 1 && dp[i][j - 1] && stones[i] - stones[j - 1] <= dis + 1) ||
                    (j >= 2 && dp[i][j - 2] && stones[i] - stones[j - 2] <= dis + 1);
            }
        return *max_element(dp[n - 1].begin(), dp[n - 1].end());
    }
};
