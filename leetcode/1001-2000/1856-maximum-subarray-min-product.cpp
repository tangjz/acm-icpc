class Solution {
public:
    int maxSumMinProduct(vector<int>& nums) {
        typedef long long LL;
        int n = nums.size();
        nums.insert(nums.begin(), -1);
        nums.push_back(-1);
        vector<int> pL(n + 2), pR(n + 2);
        iota(pL.begin(), pL.end(), 0);
        iota(pR.begin(), pR.end(), 0);
        vector<LL> psum = {0};
        for(int i = 1; i <= n; ++i) {
            psum.push_back(psum.back() + nums[i]);
            for(--pL[i]; nums[pL[i]] >= nums[i]; pL[i] = pL[pL[i]]);
        }
        LL ans = 0;
        for(int i = n; i >= 1; --i) {
            for(++pR[i]; nums[pR[i]] >= nums[i]; pR[i] = pR[pR[i]]);
            ans = max(ans, (LL)nums[i] * (psum[pR[i] - 1] - psum[pL[i]]));
        }
        return ans % ((int)1e9 + 7);
    }
};
