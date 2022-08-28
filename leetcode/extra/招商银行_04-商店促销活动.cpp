class Solution {
public:
    int goShopping(vector<int>& A, vector<int>& B) {
        int n = B.size();
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return B[u] > B[v];
        });
        typedef long long LL;
        int cur = 0, pre = 1;
        static LL dp[2][3][4];
        auto upd_min = [&](LL &x, LL y) {
            x > y && (x = y);
        };
        memset(dp[cur], 0x3f, sizeof dp[0]);
        dp[cur][0][0] = 0;
        for(int u: ord) {
            swap(cur, pre);
            memset(dp[cur], 0x3f, sizeof dp[0]);
            LL cA = A[u] * 7LL, cB = B[u] * 10LL, cC = min(A[u], B[u]) * 10LL;
            // printf("u %d a %d b %d c %d\n", u, cA, cB, cC);
            for(int i = 0; i < 3; ++i)
                for(int j = 0, k; j <= 3; ++j) {
                    upd_min(dp[cur][i][j], dp[pre][i][j] + cC);
                    k = min(j + 1, 3);
                    upd_min(dp[cur][i][k], dp[pre][i][j] + cA);
                    k = (i + 1) % 3;
                    upd_min(dp[cur][k][j], dp[pre][i][j] + (k ? cB : 0));
                }
            // for(int i = 0; i < 3; ++i)
            //     for(int j = 0; j <= 3; ++j)
            //         if(dp[cur][i][j] < (int)1e9)
            //             printf("%d %d %d: %d\n", u, i, j, dp[cur][i][j]);
        }
        // puts("");
        return min(dp[cur][0][0], dp[cur][0][3]) / 10;
    }
};
