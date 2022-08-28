class Solution {
public:
    int findMin(vector<int>& nums) {
        int sz = (int)nums.size(), L = 0, R = sz - 1;
        while(L < R) {
            int M = (L + R) >> 1;
            bool eq = nums[L] == nums[R];
            if(nums[M] <= nums[R] - eq) {
                R = M;
            } else if(nums[M] >= nums[L] + eq) {
                L = M + 1;
            } else {
                ++L;
            }
        }
        return nums[L];
    }
};
