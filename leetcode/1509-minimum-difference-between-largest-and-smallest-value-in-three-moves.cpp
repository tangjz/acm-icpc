class Solution {
public:
    int minDifference(vector<int>& nums) {
        int n = (int)nums.size();
        if(n <= 4)
            return 0;
        sort(nums.begin(), nums.end());
        int ans = nums.back() - nums.front();
        for(int i = 0; i <= 3; ++i)
            ans = min(ans, nums[n - 4 + i] - nums[i]);
        return ans;
    }
};
