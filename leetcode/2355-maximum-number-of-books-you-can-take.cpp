class Solution {
public:
    long long maximumBooks(vector<int>& books) {
        typedef long long LL;
        int n = books.size();
        LL ans = 0;
        vector<int> pL(n);
        vector<LL> dp(n);
        for(int i = 0; i < n; ++i) {
            for(pL[i] = i - 1; pL[i] >= 0 && books[pL[i]] - pL[i] >= books[i] - i; pL[i] = pL[pL[i]]);
            int len = min(i - pL[i], books[i]);
            dp[i] = len * (books[i] + books[i] - len + 1LL) / 2 + (i - pL[i] == len && pL[i] >= 0 ? dp[pL[i]] : 0);
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
