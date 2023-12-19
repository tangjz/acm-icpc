class Solution {
public:
    int minimumChanges(string s, int k) {
        static const int maxn = 201;
        int n = s.size();
        static int dif[maxn][maxn][maxn], w[maxn][maxn], f[maxn][maxn];
        for(int d = 1; d < n; ++d) {
            for(int i = 0; i < n; ++i) {
                dif[d][i][i] = 0;
                if(i + d < n)
                    dif[d][i][i + d] = s[i] != s[i + d];
            }
            for(int len = 3; d * (len - 1) < n; ++len)
                for(int L = 0, R = d * (len - 1); R < n; ++L, ++R)
                    dif[d][L][R] = dif[d][L + d][R - d] + (s[L] != s[R]);
        }
        for(int i = 0; i < n; ++i) {
            // w[i][i] = 0;
            // if(i + 1 < n)
            //     w[i][i + 1] = s[i] != s[i + 1];
            for(int j = i; j < n; ++j)
                w[i][j] = INT_MAX;
        }
        // for(int len = 3; len <= n; ++len)
        //     for(int L = 0, R = len - 1; R < n; ++L, ++R)
        //         w[L][R] = min(w[L][R], w[L + 1][R - 1] + (s[L] != s[R]));
        for(int d = 1; d < n; ++d)
            for(int len = d + d; len <= n; len += d)
                for(int L = 0, R = len - 1; R < n; ++L, ++R) {
                    int tmp = 0;
                    for(int r = 0; r < d; ++r)
                        tmp += dif[d][L + r][R - d + 1 + r];
                    w[L][R] = min(w[L][R], tmp);
                }
        for(int i = 0; i <= k; ++i)
            for(int j = 0; j <= n; ++j)
                f[i][j] = INT_MAX;
        f[0][0] = 0;
        for(int i = 0; i < k; ++i)
            for(int j = 0; j < n; ++j) {
                if(f[i][j] == INT_MAX)
                    continue;
                for(int x = j; x < n; ++x)
                    if(w[j][x] < INT_MAX)
                        f[i + 1][x + 1] = min(f[i + 1][x + 1], f[i][j] + w[j][x]);
            }
        return f[k][n];
    }
};
