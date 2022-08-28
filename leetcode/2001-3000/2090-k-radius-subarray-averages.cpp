class Solution {
public:
    vector<int> getAverages(vector<int>& nums, int k) {
        typedef long long LL;
        int n = nums.size();
        vector<LL> psum = {0LL};
        for(int x: nums) {
            psum.push_back(psum.back() + x);
        }
        vector<int> ret(n, -1);
        for(int i = 0; i < n; ++i) {
            int L = i - k, R = i + k;
            if(L < 0 || R >= n)
                continue;
            int v = (psum[R + 1] - psum[L]) / (R - L + 1);
            ret[i] = v;
        }
        return ret;
    }
};
