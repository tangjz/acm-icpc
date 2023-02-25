class Solution {
public:
    int squareFreeSubsets(vector<int>& nums) {
        const int maxp = 10, pr[maxp] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}, mod = (int)1e9 + 7;
        vector<int> f(1 << maxp);
        f[0] = 1;
        for(int x: nums) {
            int msk = 0;
            for(int i = 0; i < maxp; ++i) {
                int c = 0;
                for( ; x % pr[i] == 0; x /= pr[i], ++c);
                if(c >= 2) {
                    msk = 1 << maxp;
                    break;
                }
                msk |= c << i;
            }
            if(msk == (1 << maxp))
                continue;
            for(int i = (1 << maxp) - 1; i >= 0; --i)
                if((i & msk) == msk)
                    (f[i] += f[i ^ msk]) >= mod && (f[i] -= mod);
        }
        int ans = mod - 1;
        for(int i = 0; i < (1 << maxp); ++i)
            (ans += f[i]) >= mod && (ans -= mod);
        return ans;
    }
};
