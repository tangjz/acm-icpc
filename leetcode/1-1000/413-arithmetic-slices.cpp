class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        for(int i = 0, j = 0; i < n; ++i) {
            for(j = max(j, i + 1); j + 1 < n && nums[j - 1] + nums[j + 1] == nums[j] * 2; ++j);
            ans += j - i - 1;
        }
        return ans;
    }
};
