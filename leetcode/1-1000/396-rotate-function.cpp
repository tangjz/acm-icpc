class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        int n = nums.size(), sum = 0, cur = 0, ans;
        for(int i = 0; i < n; ++i) {
            cur += nums[i] * i;
            sum += nums[i];
        }
        ans = cur;
        for(int i = 1; i < n; ++i) {
            cur += sum - n * nums[n - i];
            ans = max(ans, cur);
        }
        return ans;
    }
};
