class Solution {
public:
    int binarySearchableNumbers(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        vector<int> suf(n);
        suf[n - 1] = INT_MAX;
        for(int i = n - 1; i > 0; --i)
            suf[i - 1] = min(suf[i], nums[i]);
        for(int i = 0, pre = INT_MIN; i < n; ++i) {
            ans += pre <= nums[i] && nums[i] <= suf[i];
            pre = max(pre, nums[i]);
        }
        return ans;
    }
};
