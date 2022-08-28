class Solution {
public:
    int minimumXORSum(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> dp(1 << n, INT_MAX);
        dp[0] = 0;
        for(int i = 0; i < (1 << n) - 1; ++i) {
            int c = __builtin_popcount(i);
            for(int j = 0, tmp = i; j < n; ++j, tmp >>= 1) {
                if(tmp & 1)
                    continue;
                dp[i | (1 << j)] = min(dp[i | (1 << j)], dp[i] + (nums1[c] ^ nums2[j]));
            }
        }
        return dp.back();
    }
};
