class Solution {
public:
    int search(vector<int>& nums, int target) {
        int L = 0, R = (int)nums.size() - 1, ans = INT_MAX;
        while(L < R) {
            if(nums[R] < target && target < nums[L])
                break;
            int M = (L + R) >> 1;
            if(nums[L] == target) {
                ans = min(ans, L);
                break;
            }
            if(nums[M] == target) {
                ans = min(ans, M);
                R = M - 1;
                continue;
            }
            if(nums[L] == nums[M]) {
                L = L + 1;
            } else if(nums[L] < nums[M]) {
                if(nums[L] <= target && target <= nums[M]) {
                    R = M;
                } else {
                    L = M + 1;
                }
            } else {
                if(nums[M] <= target && target <= nums[R]) {
                    L = M + 1;
                } else {
                    R = M;
                }
            }
        }
        if(L == R && nums[L] == target)
            ans = min(ans, L);
        return ans < INT_MAX ? ans : -1;
    }
};
