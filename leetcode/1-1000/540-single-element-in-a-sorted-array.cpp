class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int L = 0, R = (int)nums.size() - 1;
        while(L < R) {
            int M = ((L + R) >> 2) << 1;
            if(nums[M] == nums[M + 1]) {
                L = M + 2;
            } else {
                R = M;
            }
        }
        return nums[L];
    }
};
