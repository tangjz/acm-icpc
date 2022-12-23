class Solution {
public:
    vector<int> applyOperations(vector<int>& nums) {
        int n = nums.size(), m = 0;
        for(int i = 0; i < n; ++i)
            if(i + 1 < n && nums[i] > 0 && nums[i] == nums[i + 1]) {
                nums[m++] = nums[i] * 2;
                ++i;
            } else if(nums[i] > 0) {
                nums[m++] = nums[i];
            }
        for(int i = m; i < n; ++i)
            nums[i] = 0;
        return nums;
    }
};
