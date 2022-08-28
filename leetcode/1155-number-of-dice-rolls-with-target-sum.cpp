class Solution {
public:
    int numRollsToTarget(int n, int k, int target) {
        if(target < n || target > n * k)
            return 0;
        target -= n;
        const int mod = (int)1e9 + 7;
        vector<int> dp(target + 1);
        dp[0] = 1;
        while(n--)
            for(int i = target; i > 0; --i)
                for(int j = 1; j < k && j <= i; ++j)
                    (dp[i] += dp[i - j]) >= mod && (dp[i] -= mod);
        return dp.back();
    }
};
