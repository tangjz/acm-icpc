class Solution {
public:
    int minNumberOfSemesters(int n, vector<vector<int>>& dependencies, int k) {
        const int maxs = 1 << 15 | 1;
        static int bits[maxs], msk[maxs], dp[maxs];
        int all = 1 << n;
        memset(msk, 0, all * sizeof(int));
        for(auto &it : dependencies)
            msk[1 << (--it[1])] |= 1 << (--it[0]);
        dp[0] = 0;
        for(int i = 1; i < all; ++i) {
            bits[i] = bits[i >> 1] + (i & 1);
            int lbt = i & -i;
            if(i != lbt)
                msk[i] = msk[i ^ lbt] | msk[lbt];
            if(bits[i] > k)
                msk[i] = all;
            dp[i] = n;
            for(int j = i, k; j > 0; j = (j - 1) & i) {
                k = i ^ j;
                if((msk[j] & k) == msk[j]) {
                    k = dp[k] + 1;
                    dp[i] > k && (dp[i] = k);
                }
            }
        }
        return dp[all - 1];
    }
};
