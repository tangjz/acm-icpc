class Solution {
public:
    int waysToMakeFair(vector<int>& nums) {
        int n = nums.size();
        vector<int> pre(n), suf(n);
        for(int i = 0; i < n; ++i) {
            pre[i] = nums[i] + (i > 1 ? pre[i - 2] : 0);
        }
        for(int i = n - 1; i >= 0; --i) {
            suf[i] = nums[i] + (i + 2 < n ? suf[i + 2] : 0);
        }
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            int odd = 0, even = 0;
            if(i > 0) {
                odd += pre[i - 1];
                even += i > 1 ? pre[i - 2] : 0;
            }
            if(i + 1 < n) {
                even += suf[i + 1];
                odd += i + 2 < n ? suf[i + 2] : 0;
            }
            ans += even == odd;
        }
        return ans;
    }
};
