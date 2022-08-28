class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ans = nums.front(), sum = 0;
        for(int x : nums) {
            sum = x + max(sum, 0);
            ans = max(ans, sum);
        }
        return ans;
    }
};
