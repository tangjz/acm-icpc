class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int> > dp(m + 1, vector<int>(n + 1));
        for(auto &it: strs) {
            int c[2] = {};
            for(char ch: it)
                ++c[(int)(ch - '0')];
            for(int i = m; i >= c[0]; --i)
                for(int j = n; j >= c[1]; --j)
                    dp[i][j] = max(dp[i][j], dp[i - c[0]][j - c[1]] + 1);
        }
        return dp[m][n];
    }
};
