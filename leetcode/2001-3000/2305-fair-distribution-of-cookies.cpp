class Solution {
public:
    int distributeCookies(vector<int>& cookies, int k) {
        const int INF = 0x3f3f3f3f;
        int n = cookies.size();
        vector<int> s(1 << n);
        vector<vector<int> > dp(k + 1, vector<int>(1 << n, INF));
        dp[0][0] = 0;
        for(int i = 1; i < (1 << n); ++i) {
            for(int j = 0; j < n; ++j)
                if((i >> j) & 1)
                    s[i] += cookies[j];
            for(int j = i; j; j = (j - 1) & i)
                for(int c = 1; c <= k; ++c)
                    dp[c][i] = min(dp[c][i], max(dp[c - 1][i ^ j], s[j]));
        }
        return dp[k].back();
    }
};
