class Solution {
public:
    int triangularSum(vector<int>& nums) {
        int n = nums.size();
        while(n > 1) {
            for(int i = 0; i + 1 < n; ++i) {
                nums[i] = (nums[i] + nums[i + 1]) % 10;
            }
            nums.pop_back();
            --n;
        }
        return nums.back();
    }
};
