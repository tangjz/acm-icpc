class Solution {
public:
    long long getSchemeCount(int n, int m, vector<string>& mat) {
        typedef long long LL;
        if(n < m) {
            vector<string> rev(m);
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < m; ++j)
                    rev[j].push_back(mat[i][j]);
            mat = move(rev);
            swap(n, m);
        }
        static constexpr int maxm = 6, pw13[] = {1, 13, 169, 2197, 28561, 371293}, maxs = pw13[maxm - 1];
        static const int tr[][3] = {
            {0, 0, 0},
            {0, 1, 0},
            {0, 1, 1},
            {0, 1, 2},
            {0, 2, 0},
            {0, 2, 1},
            {0, 2, 2},
            {1, 0, 0},
            {1, 1, 0},
            {1, 2, 0},
            {2, 0, 0},
            {2, 1, 0},
            {2, 2, 0},
        }, nxt[][3] = {
            {0, 7, 10},
            {1, 8, 11},
            {2, 8, -1},
            {3, -1, 11},
            {4, 9, 12},
            {5, 9, -1},
            {6, -1, 12},
            {1, 8, 11},
            {2, 8, -1},
            {3, -1, 11},
            {4, 9, 12},
            {5, 9, -1},
            {6, -1, 12},
        };
        static int cur = 0, pre = 1;
        static LL dp[2][maxs];
        int sz = pw13[m];
        memset(dp[cur], 0, sz * sizeof(LL));
        dp[cur][0] = 1;
        for(int x = 0; x < n; ++x)
            for(int y = 0; y < m; ++y) {
                swap(cur, pre);
                memset(dp[cur], 0, sz * sizeof(LL));
                int pL = -1, pR = 0;
                switch(mat[x][y]) {
                    case '.': {
                        pL = pR = 0;
                        break;
                    }
                    case 'B': {
                        pL = pR = 1;
                        break;
                    }
                    case 'R': {
                        pL = pR = 2;
                        break;
                    }
                    case '?': {
                        pL = 0;
                        pR = 2;
                        break;
                    }
                }
                static int seq[maxm + 1], sp[2];
                memset(seq, 0, (y + 1) * sizeof(int));
                seq[0] = -1;
                for(int u = 0; u < sz; ++u) {
                    ++seq[0];
                    for(int i = 0; i <= y && seq[i] == 13; seq[i++] = 0, ++seq[i]);
                    if(!dp[pre][u])
                        continue;
                    // printf("x = %d, y = %d, u = %d: %lld\n", x, y, u, dp[pre][u]);
                    // for(int i = 0, rem = u; i < m; ++i) {
                    //     int rep = rem % 13;
                    //     rem /= 13;
                    //     if(i >= y)
                    //         putchar('x');
                    //     for(int j = 0; j < 3; ++j)
                    //         printf("%d", tr[rep][j]);
                    //     if(i < y)
                    //         putchar('x');
                    //     putchar('\n');
                    // }
                    int c = 0;
                    for(int i = y - 1; c < 2 && i >= 0; --i) {
                        int o = tr[seq[i]][0];
                        if(o)
                            sp[c++] = o;
                    }
                    for(int p = pL; p <= pR; ++p) {
                        if(p && c == 2 && p != sp[1])
                            continue;
                        int o = nxt[seq[y]][p];
                        if(o == -1)
                            continue;
                        int v = u + (o - seq[y]) * pw13[y];
                        dp[cur][v] += dp[pre][u];
                    }
                }
            }
        LL ans = 0;
        for(int i = 0; i < sz; ++i)
            ans += dp[cur][i];
        return ans;
    }
};
