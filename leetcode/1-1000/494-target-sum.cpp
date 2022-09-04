class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int n = nums.size(), R = accumulate(nums.begin(), nums.end(), 0), L = -R;
        if(target < L || target > R)
            return 0;
        int len = R - L + 1;
        vector<int> f(len), g;
        f[-L] = 1;
        for(int x: nums) {
            g.assign(len, 0);
            for(int i = 0; i < len; ++i)
                if(f[i]) {
                    g[i + x] += f[i];
                    g[i - x] += f[i];
                }
            f.swap(g);
        }
        return f[target - L];
    }
};
