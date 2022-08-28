class Solution {
public:
    int countHillValley(vector<int>& nums) {
        nums.erase(unique(nums.begin(), nums.end()), nums.end());
        int n = nums.size(), ans = 0;
        for(int i = 1; i + 1 < n; ++i) {
            ans += (nums[i] - nums[i - 1]) * (nums[i] - nums[i + 1]) > 0;
        }
        return ans;
    }
};
