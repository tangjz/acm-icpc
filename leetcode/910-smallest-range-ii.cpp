class Solution {
public:
    int smallestRangeII(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int ans = nums.back() - nums.front(), n = nums.size();
        for(int i = 1; i < n; ++i) {
            int low = min(nums[0], nums[i] - k - k);
            int upp = max(nums[i - 1], nums[n - 1] - k - k);
            ans = min(ans, upp - low);
        }
        return ans;
    }
};
