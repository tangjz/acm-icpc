class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int L = 0, R = (int)nums.size();
        while(L < R) {
            int M = (L + R) >> 1;
            if(nums[M] >= target) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        return L;
    }
};
