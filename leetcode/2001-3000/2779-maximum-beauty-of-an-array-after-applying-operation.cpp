class Solution {
public:
    int maximumBeauty(vector<int>& nums, int k) {
        int n = nums.size(), ans = 0;
        sort(nums.begin(), nums.end());
        for(int i = 0, j = 0; i < n; ++i) {
            for( ; j + 1 < n && nums[j + 1] - nums[i] <= k + k; ++j);
            ans = max(ans, j - i + 1);
        }
        return ans;
    }
};
