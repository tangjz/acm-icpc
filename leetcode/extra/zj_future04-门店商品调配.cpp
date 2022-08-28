class Solution {
public:
    int minTransfers(vector<vector<int>>& distributions) {
        const int maxd = 12, maxs = 1 << maxd | 1;
        int n = 0;
        vector<int> sum(maxs), dp(maxs);
        for(auto &it: distributions) {
            n = max(n, max(it[0], it[1]) + 1);
            sum[1 << it[0]] -= it[2];
            sum[1 << it[1]] += it[2];
        }
        int m = 1 << n;
        for(int i = 1; i < m; ++i) {
            int lbt = i & -i;
            if(lbt < i)
                sum[i] = sum[i ^ lbt] + sum[lbt];
            for(int j = 1; j < m; j <<= 1)
                if(i & j)
                    dp[i] = max(dp[i], dp[i ^ j]);
            if(!sum[i])
                ++dp[i];
        }
        return n - dp[m - 1];
    }
};
