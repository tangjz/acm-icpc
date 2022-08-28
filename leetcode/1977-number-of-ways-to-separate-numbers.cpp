class Solution {
public:
    int numberOfCombinations(string num) {
        const int mod = (int)1e9 + 7;
        int n = num.length();
        vector<vector<int> > lcp(n, vector<int>(n)), dp(n, vector<int>(n));
        for(int i = n - 1; i >= 0; --i)
            for(int j = n - 1; j >= 0; --j)
                lcp[i][j] = i < j ? lcp[j][i] : (i + 1 < n && num[i] == num[j] ? lcp[i + 1][j + 1] + 1 : 0);
        for(int M = 0; M < n; ++M) {
            if(num[0] != '0')
                dp[0][M] = 1;
            // for(int L = 0; L <= M; ++L)
            //     printf("dp[%d][%d]=%d\n", L, M, dp[L][M]);
            if(M + 1 == n || num[M + 1] == '0')
                continue;
            int L = M + 1, sum = 0;
            for(int R = M + 1; R < n; ++R) {
                while(L > 0) {
                    int lft = M - L + 2, rht = R - M;
                    if(lft > rht)
                        break;
                    if(lft == rht) {
                        int len = lcp[L - 1][M + 1];
                        if(len < lft && num[L - 1 + len] > num[M + 1 + len])
                            break;
                    }
                    --L;
                    if(num[L] != '0')
                        (sum += dp[L][M]) >= mod && (sum -= mod);
                }
                // num[L..M] <= num[M+1..R]
                (dp[M + 1][R] += sum) >= mod && (dp[M + 1][R] -= mod);
            }
        }
        // puts("");
        int ans = 0;
        for(int L = 0; L < n; ++L)
            (ans += dp[L][n - 1]) >= mod && (ans -= mod);
        return ans;
    }
};
