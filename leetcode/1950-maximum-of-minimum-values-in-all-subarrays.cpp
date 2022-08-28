class Solution {
public:
    vector<int> findMaximums(vector<int>& nums) {
        int n = nums.size();
        vector<int> pL(n), pR(n), ret(n);
        for(int i = 0; i < n; ++i)
            for(pL[i] = i - 1; pL[i] >= 0 && nums[i] <= nums[pL[i]]; pL[i] = pL[pL[i]]);
        for(int i = n - 1; i >= 0; --i) {
            for(pR[i] = i + 1; pR[i] < n && nums[i] <= nums[pR[i]]; pR[i] = pR[pR[i]]);
            int upp = pR[i] - pL[i] - 2;
            ret[upp] = max(ret[upp], nums[i]);
        }
        for(int i = n - 1; i > 0; --i)
            ret[i - 1] = max(ret[i - 1], ret[i]);
        return ret;
    }
};
