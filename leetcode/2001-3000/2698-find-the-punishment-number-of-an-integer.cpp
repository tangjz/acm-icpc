class Solution {
public:
    int punishmentNumber(int n) {
        static const int maxn = 1001, maxl = 9;
        static int ok = 0, f[maxn] = {};
        if(!ok) {
            ok = 1;
            for(int i = 1; i < maxn; ++i) {
                static char buf[maxl];
                static bool dp[maxl][maxn] = {};
                int len = sprintf(buf, "%d", i * i);
                for(int j = 0; j <= len; ++j)
                    memset(dp[j], 0, (i + 1) * sizeof(bool));
                dp[0][0] = 1;
                for(int j = 0; j < len; ++j)
                    for(int k = j, sum = 0; k < len; ++k) {
                        sum = sum * 10 + (buf[k] - '0');
                        if(sum > i)
                            break;
                        for(int u = sum; u <= i; ++u)
                            dp[k + 1][u] |= dp[j][u - sum];
                    }
                if(dp[len][i])
                    f[i] = i * i;
                f[i] += f[i - 1];
            }
        }
        return f[n];
    }
};
