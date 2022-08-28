class Solution {
public:
    int waysToSplitArray(vector<int>& nums) {
        typedef long long LL;
        vector<LL> psum = {0};
        for(int x: nums)
            psum.push_back(psum.back() + x);
        int n = nums.size(), ans = 0;
        for(int i = 0; i + 1 < n; ++i) {
            ans += psum[i + 1] >= psum[n] - psum[i + 1];
        }
        return ans;
    }
};
