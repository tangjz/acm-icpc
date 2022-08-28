class Solution {
public:
    int findMin(vector<int>& nums) {
        int L = 0, R = nums.size() - 1;
        while(L + 1 < R && nums[L] > nums[R]) {
            int M = (L + R) >> 1;
            if(nums[M] >= nums[L]) {
                L = M;
            } else {
                R = M;
            }
        }
        return min(nums[L], nums[R]);
    }
};
