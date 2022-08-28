class Solution {
public:
    long long maximumAlternatingSubarraySum(vector<int>& nums) {
        typedef long long LL;
        int n = nums.size();
        LL low = 0, upp = 0, ans = LLONG_MIN;
        for(int i = n - 1; i >= 0; --i) {
            ans = max(ans, nums[i] - low);
            tie(low, upp) = make_pair(min(nums[i] - upp, 0LL), max(nums[i] - low, 0LL));
        }
        return ans;
    }
};
