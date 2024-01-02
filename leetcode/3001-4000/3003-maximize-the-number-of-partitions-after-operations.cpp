class Solution {
public:
    int maxPartitionsAfterOperations(string s, int k) {
        static const int maxn = (int)1e4 + 1, maxc = 26, maxd = 14, maxs = 1 << 26 | 1;
        if(k == maxc)
            return 1;
        int n = s.size();
        if(k == 1) {
            int ans = 0, adt = 0;
            for(int i = 0, j; i < n; ++ans) {
                for(j = i; i < n && s[i] == s[j]; ++i);
                adt = max(adt, i - j - 1);
            }
            return ans + min(adt, 2);
        }
        static int bits[maxs] = {}, msk[maxd + 1][maxn], dp[maxc + 3][maxn];
        if(!bits[1])
            for(int i = 1; i < maxs; ++i)
                bits[i] = bits[i >> 1] + (i & 1);
        for(int i = 0; i < n; ++i)
            msk[0][i] = 1 << (s[i] - 'a');
        for(int i = 1; i < maxd; ++i)
            for(int j = 0; j + (1 << i) <= n; ++j)
                msk[i][j] = msk[i - 1][j] | msk[i - 1][j + (1 << (i - 1))];
        for(int i = 0; i < maxc + 2; ++i)
            memset(dp[i], -1, (n + 1) * sizeof(int));
        dp[maxc][0] = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < maxc + 2; ++j) {
                if(dp[j][i] < 0)
                    continue;
                // printf("%d %d: %d\n", j, i, dp[j][i]);
                int ii = i + 1, cur = 1 << (j < maxc ? j : s[i] - 'a');
                for(int d = maxd - 1; d >= 0; --d) {
                    if(ii + (1 << d) > n)
                        continue;
                    int nxt = cur | msk[d][ii];
                    if(bits[nxt] >= k)
                        continue;
                    ii += 1 << d;
                    cur = nxt;
                }
                if(ii < n) {
                    int o = s[ii] - 'a';
                    if(ii - i >= k && j == maxc)
                        dp[maxc + 1][ii] = max(dp[maxc + 1][ii], dp[j][i] + 1);
                    cur |= msk[0][ii++];
                }
                if(ii == n) {
                    dp[maxc + 1][n] = max(dp[maxc + 1][n], dp[j][i] + 1);
                    continue;
                }
                if(j == maxc) {
                    // printf("cur: %d\n", cur);
                    for(int jj = 0; jj < maxc; ++jj)
                        if(!(cur & (1 << jj))) {
                            // printf("%d %d -> %d %d\n", j, i, jj, ii);
                            dp[jj][ii] = max(dp[jj][ii], dp[j][i] + 1);
                        }
                }
                for(int d = maxd - 1; d >= 0; --d) {
                    if(ii + (1 << d) > n)
                        continue;
                    int nxt = cur | msk[d][ii];
                    if(bits[nxt] > k)
                        continue;
                    ii += 1 << d;
                    cur = nxt;
                }
                int jj = j < maxc ? maxc + 1 : j;
                dp[jj][ii] = max(dp[jj][ii], dp[j][i] + 1);
            }
        // puts("");
        int ans = -1;
        for(int i = 0; i < maxc + 2; ++i) {
            // printf("%d %d: %d\n", i, n, dp[i][n]);
            ans = max(ans, dp[i][n]);
        }
        return ans;
    }
};
