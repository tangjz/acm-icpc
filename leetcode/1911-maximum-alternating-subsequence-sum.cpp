class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        typedef long long LL;
        const LL INF = (LL)1e11;
        LL f[2] = {0, -INF};
        for(int x: nums) {
            LL u = max(f[0], f[1] - x), v = max(f[1], f[0] + x);
            f[0] = u;
            f[1] = v;
        }
        return max(f[0], f[1]);
    }
};
