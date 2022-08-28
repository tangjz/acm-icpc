class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int L = 0, R = (int)nums.size() - 1;
        while(L < R) {
            if(nums[R] < target && target < nums[L])
                return 0;
            int M = (L + R) >> 1;
            if(nums[M] == target)
                return 1;
            if(nums[L] == nums[M]) {
                L = L + 1;
            } else if(nums[L] < nums[M]) {
                if(nums[L] <= target && target <= nums[M]) {
                    R = M;
                } else {
                    L = M + 1;
                }
            } else {
                if(nums[M] < target && target <= nums[R]) {
                    L = M + 1;
                } else {
                    R = M;
                }
            }
        }
        return L == R && nums[L] == target;
    }
};
