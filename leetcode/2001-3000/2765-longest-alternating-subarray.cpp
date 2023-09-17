class Solution {
public:
    int alternatingSubarray(vector<int>& nums) {
        int n = nums.size(), ans = -1;
        for(int i = n - 1; i > 0; --i)
            nums[i] -= nums[i - 1];
        for(int i = 1, j; i < n; ) {
            if(nums[i] != 1) {
                ++i;
                continue;
            }
            for(j = i++; i < n && nums[i] + nums[i - 1] == 0; ++i);
            ans = max(ans, i - j + 1);
        }
        return ans;
    }
};
