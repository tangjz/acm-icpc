class Solution {
public:
    int missingElement(vector<int>& nums, int k) {
        int L = 0, R = nums.size() - 1;
        while(L < R) {
            int M = (L + R + 1) >> 1;
            int cnt = nums[M] - nums[0] - M;
            if(cnt >= k) {
                R = M - 1;
            } else {
                L = M;
            }
        }
        return nums[0] + L + k;
    }
};
