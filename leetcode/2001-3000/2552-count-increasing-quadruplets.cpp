class Solution {
public:
    long long countQuadruplets(vector<int>& nums) {
        typedef long long LL;
        int n = nums.size();
        vector<LL> pre(n);
        vector<vector<LL> > suf(n, vector<LL>(n));
        for(int i = n - 1; i >= 0; --i) {
            int v = nums[i] - 1;
            for(int j = 0; j <= v; ++j)
                ++suf[i][j];
            if(i > 0)
                suf[i - 1] = suf[i];
        }
        LL ans = 0;
        for(int i = 0; i < n; ++i) {
            int v = nums[i] - 1;
            if(i > 0 && v + 1 < n)
                for(int j = i + 1; j + 1 < n; ++j) {
                    int w = nums[j] - 1;
                    if(w > 0 && v > w)
                        ans += pre[w - 1] * suf[j + 1][v + 1];
                }
            for(int j = v; j < n; ++j)
                ++pre[j];
        }
        return ans;
    }
};
