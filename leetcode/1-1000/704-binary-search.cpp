class Solution {
public:
    int search(vector<int>& nums, int target) {
        for(int L = 0, R = nums.size(); L < R; ) {
            int M = (L + R) / 2, v = nums[M];
            if(v == target) {
                return M;
            }
            if(v > target) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        return -1;
    }
};
