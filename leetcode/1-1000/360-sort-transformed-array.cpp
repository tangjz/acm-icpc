class Solution {
public:
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
        int n = nums.size(), p = 0;
        bool rev = 0;
        if(a) {
            rev = a < 0;
            int mid = -b / (a + a);
            for( ; p < n && nums[p] < mid; ++p);
        } else if(b < 0) {
            p = n;
        }
        for(int &x: nums)
            x = (a * x + b) * x + c;
        if(rev) {
            reverse(nums.begin() + p, nums.end());
        } else {
            reverse(nums.begin(), nums.begin() + p);
        }
        inplace_merge(nums.begin(), nums.begin() + p, nums.end());
        return nums;
    }
};
