class Solution {
public:
    int largestPerimeter(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        reverse(nums.begin(), nums.end());
        int n = nums.size();
        for(int i = 2; i < n; ++i)
            if(nums[i - 2] < nums[i - 1] + nums[i])
                return nums[i - 2] + nums[i - 1] + nums[i];
        return 0;
    }
};
