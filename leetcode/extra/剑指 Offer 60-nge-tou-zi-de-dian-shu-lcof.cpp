class Solution {
public:
    vector<double> dicesProbability(int n) {
        vector<int> dp(n * 6 + 1);
        dp[0] = 1;
        for(int i = 0; i < n; ++i)
            for(int j = n * 6; j >= 0; --j) {
                if(!dp[j])
                    continue;
                for(int k = 1; k <= 6; ++k)
                    dp[j + k] += dp[j];
                dp[j] = 0;
            }
        vector<double> ret;
        ret.reserve(dp.size());
        int sum = 0;
        for(int i = n; i <= n * 6; ++i)
            sum += dp[i];
        for(int i = n; i <= n * 6; ++i)
            ret.push_back((double)dp[i] / sum);
        return ret;
    }
};
