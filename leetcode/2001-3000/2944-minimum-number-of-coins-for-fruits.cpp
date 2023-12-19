class Solution {
public:
    int minimumCoins(vector<int>& A) {
        int n = A.size(), L = 0;
        vector<int> dp(n + 1), que;
        que.push_back(n);
        for(int i = n - 1; i >= 0; --i) {
            for( ; L < que.size() && que[L] > i + i + 2; ++L);
            dp[i] = dp[que[L]] + A[i];
            for( ; L < que.size() && dp[que.back()] > dp[i]; que.pop_back());
            que.push_back(i);
        }
        return dp[0];
    }
};
