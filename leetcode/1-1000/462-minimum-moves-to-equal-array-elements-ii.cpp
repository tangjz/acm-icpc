class Solution {
public:
    int minMoves2(vector<int>& nums) {
        int n = nums.size(), m = n >> 1;
        nth_element(nums.begin(), nums.begin() + m, nums.end());
        int ans = 0, mid = nums[m];
        for(int x: nums)
            ans += abs(x - mid);
        return ans;
    }
};
