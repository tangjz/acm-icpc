class Solution {
public:
    int minimumCost(string s, int k) {
        int m = s.size();
        vector<int> pos = {0};
        for(int i = 1; i < m; ++i)
            if(s[i - 1] == ' ')
                pos.push_back(i);
        int n = pos.size(), ans = INT_MAX;
        vector<int> dp(n, INT_MAX);
        dp[0] = 0;
        for(int i = 0; i < n; ++i) {
            if(dp[i] == INT_MAX)
                continue;
            if(m - pos[i] <= k)
                ans = min(ans, dp[i]);
            for(int j = i + 1; j < n; ++j) {
                int adt = k - (pos[j] - pos[i] - 1);
                if(adt < 0)
                    break;
                dp[j] = min(dp[j], dp[i] + adt * adt);
            }
        }
        return ans;
    }
};
