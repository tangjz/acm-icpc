class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int L = 0, R = nums.size() - 1;
        while(L < R) {
            int M = (L + R) >> 1;
            if(nums[M] > nums[M + 1]) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        return L;
    }
};
