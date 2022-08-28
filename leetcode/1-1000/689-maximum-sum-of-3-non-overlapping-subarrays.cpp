class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> psum = {0};
        for(int x: nums)
            psum.push_back(psum.back() + x);
        vector<pair<int, int> > suf(n);
        for(int i = n - 1; i >= 0; --i) {
            if(i + k <= n)
                suf[i] = max(suf[i], make_pair(psum[i + k] - psum[i], -i));
            if(i + 1 < n)
                suf[i] = max(suf[i], suf[i + 1]);
        }
        pair<int, vector<int> > ans = {};
        pair<int, int> pre = {};
        for(int i = k; i <= n - k - k; ++i) {
            pre = max(pre, make_pair(psum[i] - psum[i - k], -(i - k)));
            ans = max(ans, make_pair(pre.first + psum[i + k] - psum[i] + suf[i + k].first, vector<int>{pre.second, -i, suf[i + k].second}));
        }
        for(int &x: ans.second)
            x = -x;
        return ans.second;
    }
};
