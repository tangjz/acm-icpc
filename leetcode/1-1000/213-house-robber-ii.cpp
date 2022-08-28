class Solution {
    int solve(vector<int> &nums) {
        int dp[2] = {};
        for(int x: nums) {
            int u = max(dp[0], dp[1]);
            int v = max(dp[1], dp[0] + x);
            dp[0] = u;
            dp[1] = v;
        }
        return max(dp[0], dp[1]);
    }
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 1)
            return nums.back();
        if(n == 2)
            return max(nums.front(), nums.back());
        int x = nums.back();
        nums.pop_back();
        int ans = solve(nums);
        nums.pop_back();
        reverse(nums.begin(), nums.end());
        nums.pop_back();
        return max(ans, solve(nums) + x);
    }
};
