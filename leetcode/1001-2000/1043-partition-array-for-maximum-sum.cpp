class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        typedef long long LL;
        int n = arr.size();
        vector<LL> dp(n + 1);
        for(int i = 0; i < n; ++i) {
            int upp = arr[i];
            for(int j = i; j < n && j - i + 1 <= k; ++j) {
                upp = max(upp, arr[j]);
                dp[j + 1] = max(dp[j + 1], dp[i] + upp * (j - i + 1LL));
            }
        }
        return dp.back();
    }
};
