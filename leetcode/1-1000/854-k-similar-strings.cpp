class Solution {
public:
    int kSimilarity(string s1, string s2) {
        typedef long long LL;
        const int maxd = 6, BLEN = 6, BMSK = 63, maxm = 1 << 20 | 1;
        const LL STA = 34905131040LL;
        int n = s1.size(), m = 1 << n;
        static int lbt[maxm] = {}, dp[maxm];
        static LL sum[maxm];
        if(!lbt[0]) {
            lbt[0] = -1;
            for(int i = 1; i < maxm; ++i)
                lbt[i] = i & 1 ? 0 : lbt[i >> 1] + 1;
        }
        for(int i = 1; i < m; ++i) {
            int x = lbt[i];
            dp[i] = 0;
            if((1 << x) == i) {
                sum[i] = STA + (1LL << ((s1[x] - 'a') * BLEN)) - (1LL << ((s2[x] - 'a') * BLEN));
            } else {
                x = 1 << x;
                sum[i] = sum[x] + sum[i ^ x] - STA;
                for(int j = i; j > 0; j ^= x) {
                    x = 1 << lbt[j];
                    dp[i] = max(dp[i], dp[i ^ x]);
                }
            }
            dp[i] += sum[i] == STA;
        }
        return n - dp[m - 1];
    }
};
