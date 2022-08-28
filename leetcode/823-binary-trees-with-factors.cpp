class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& arr) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int n = arr.size(), ans = 0;
        sort(arr.begin(), arr.end());
        vector<int> dp(n);
        for(int i = 0; i < n; ++i) {
            dp[i] = 1;
            for(int j = 0, k = i - 1; j <= k; ++j) {
                if(arr[i] % arr[j] > 0)
                    continue;
                int val = arr[i] / arr[j];
                for( ; j <= k && arr[k] > val; --k);
                if(j <= k && arr[k] == val)
                    dp[i] = (dp[i] + (1LL + (j < k)) * dp[j] * dp[k]) % mod;
            }
            (ans += dp[i]) >= mod && (ans -= mod);
        }
        return ans;
    }
};
