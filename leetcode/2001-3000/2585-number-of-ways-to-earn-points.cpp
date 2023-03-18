class Solution {
public:
    int waysToReachTarget(int m, vector<vector<int>>& seq) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        vector<int> dp(m + 1);
        dp[0] = 1;
        for(auto &it: seq) {
            int c = it[0], w = it[1];
            for(int i = m; i >= w; --i)
                for(int j = w, k = 1; j <= i && k <= c; j += w, ++k)
                    (dp[i] += dp[i - j]) >= mod && (dp[i] -= mod);
        }
        return dp[m];
    }
};
