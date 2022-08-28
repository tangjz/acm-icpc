class Solution {
public:
    int sumSubseqWidths(vector<int>& nums) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int n = nums.size(), ans = 0;
        sort(nums.begin(), nums.end());
        for(int i = 0, prd = 1; i < n; ++i) {
            ans = (ans + (LL)prd * (nums[i] - nums[n - 1 - i])) % mod;
            prd = 2LL * prd % mod;
        }
        return ans < 0 ? ans + mod : ans;
    }
};
