class Solution {
public:
    int longestPalindrome(string a, string b) {
        const int maxn = (int)2e3 + 1;
        int n = (int)a.size(), m = (int)b.size(), len = n + m;
        static char buf[maxn];
        static int msk[maxn], dp[3][maxn][maxn];
        for(int i = 1; i < 4; ++i)
            for(int L = 0; L < len; ++L)
                for(int R = L; R < len; ++R)
                    dp[i - 1][L][R] = INT_MIN;
        for(int i = 0; i < len; ++i) {
            buf[i] = i < n ? a[i] : b[i - n];
            msk[i] = i < n ? 1 : 2;
            dp[msk[i] - 1][i][i] = 1;
            if(i > 0 && buf[i - 1] == buf[i]) {
                dp[(msk[i] | msk[i - 1]) - 1][i - 1][i] = 2;
            }
        }
        auto upd_max = [&](int &x, int y) -> void {
            x < y && (x = y);
        };
        for(int i = 2; i <= len; ++i) {
            for(int L = 0, R = i - 1; R < len; ++L, ++R) {
                if(i > 2 && buf[L] == buf[R]) {
                    int adt = msk[L] | msk[R];
                    for(int d = 1; d < 4; ++d)
                        upd_max(dp[(d | adt) - 1][L][R], dp[d - 1][L + 1][R - 1] + 2);
                }
                for(int d = 1; d < 4; ++d) {
                    upd_max(dp[d - 1][L][R], dp[d - 1][L + 1][R]);
                    upd_max(dp[d - 1][L][R], dp[d - 1][L][R - 1]);
                }
            }
        }
        return max(dp[3 - 1][0][len - 1], 0);
    }
};
