class Solution {
public:
    int minPairSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int ans = 0;
        for(int i = 0, j = n - 1; i < j; ++i, --j)
            ans = max(ans, nums[i] + nums[j]);
        return ans;
    }
};
