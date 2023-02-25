class Solution {
public:
    int minimumPartition(string s, int k) {
        int n = s.size();
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for(int i = 0; i < n; ++i) {
            if(dp[i] == INT_MAX)
                continue;
            long long v = 0;
            for(int j = i; j < n; ++j) {
                v = v * 10 + (s[j] - '0');
                if(v > k)
                    break;
                dp[j + 1] = min(dp[j + 1], dp[i] + 1);
            }
        }
        return dp[n] < INT_MAX ? dp[n] : -1;
    }
};
