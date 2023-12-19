class Solution {
public:
    int lengthOfLongestSubsequence(vector<int>& A, int m) {
        static const int maxv = 1001;
        static int dp[maxv];
        memset(dp, -1, (m + 1) * sizeof(int));
        dp[0] = 0;
        for(int x: A)
            for(int i = m; i >= x; --i)
                if(dp[i - x] != -1)
                    dp[i] = max(dp[i], dp[i - x] + 1);
        return dp[m];
    }
};
