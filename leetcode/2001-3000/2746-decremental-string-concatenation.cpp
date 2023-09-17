class Solution {
public:
    int minimizeConcatenatedLength(vector<string>& A) {
        const int maxd = 26;
        int n = A.size();
        static int dp[2][maxd + 1][maxd + 1], cur = 1, pre = 0;
        for(int i = 0; i < n; ++i) {
            swap(cur, pre);
            memset(dp[cur], 0x3f, sizeof dp[0]);
            int L = A[i].front() - 'a', R = A[i].back() - 'a', sz = A[i].size();
            if(!i) {
                dp[cur][L][R] = sz;
                continue;
            }
            for(int j = 0; j < maxd; ++j)
                for(int k = 0; k < maxd; ++k) {
                    dp[cur][j][R] = min(dp[cur][j][R], dp[pre][j][k] + sz - (k == L));
                    dp[cur][L][k] = min(dp[cur][L][k], dp[pre][j][k] + sz - (j == R));
                }
        }
        int ans = INT_MAX;
        for(int j = 0; j < maxd; ++j)
            for(int k = 0; k < maxd; ++k)
                ans = min(ans, dp[cur][j][k]);
        return ans;
    }
};
