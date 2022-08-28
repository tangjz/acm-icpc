class Solution {
public:
    int maxSumAfterOperation(vector<int>& nums) {
        int n = nums.size();
        vector<int> fL(n), fR(n), gL(n), gR(n);
        for(int i = n - 1; i >= 0; --i) {
            fR[i] = max(i + 1 < n ? fR[i + 1] : 0, 0) + nums[i];
            gR[i] = max(i + 1 < n ? gR[i + 1] : 0, fR[i]);
        }
        int ans = 0;
        for(int i = 0; i < n; ++i) {
            fL[i] = max(i > 0 ? fL[i - 1] : 0, 0) + nums[i];
            gL[i] = max(i > 0 ? gL[i - 1] : 0, fL[i]);
            int lft = 0, rht = 0;
            if(i > 0) {
                lft = max(lft, fL[i - 1]);
                ans = max(ans, gL[i - 1]);
            }
            if(i + 1 < n) {
                rht = max(rht, fR[i + 1]);
                ans = max(ans, gR[i + 1]);
            }
            ans = max(ans, lft + nums[i] * nums[i] + rht);
        }
        return ans;
    }
};
