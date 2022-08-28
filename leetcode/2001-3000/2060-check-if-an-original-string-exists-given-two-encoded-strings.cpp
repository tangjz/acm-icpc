class Solution {
    struct Bitset {
        typedef unsigned long long u64;
        int len, blen;
        vector<u64> vals;
        void init(int len) {
            this -> len = len;
            this -> blen = (len - 1) / 64 + 1;
            vals.resize(this -> blen);
        }
        bool test(int x) const {
            return x >= 0 && x < len && (vals[x >> 6] >> (x & 63)) & 1;
        }
        void set(int x) {
            if(x >= 0 && x < len)
                vals[x >> 6] |= 1ull << (x & 63);
        }
        void trans(Bitset const &src, int L, int R, int offset) { // [L, R)
            L = max(L, 0);
            R = min(R, len);
            // printf("trans %d %d %d\n", L, R, offset);
            if(L >= R)
                return;
            int dx = abs(offset) >> 6, dy = abs(offset) & 63;
            // printf("dx %d dy %d ofs %d\n", dx, dy, offset);
            for(int i = (L >> 6), j = i << 6; j < R; ++i, j += 64) {
                u64 msk = src.vals[i];
                // printf("msk %d (%d, %d]: %llu\n", i, j, j + 64, msk);
                if(j < L) {
                    msk &= ~0ull << (L - j);
                }
                if(j + 64 > R) {
                    msk &= ~0ull >> (j + 64 - R);
                }
                // printf("msk shrinked %llu\n", msk);
                if(offset < 0) {
                    if(i - dx >= 0) {
                        // printf("add %d: %llu\n", i - dx, msk >> dy);
                        vals[i - dx] |= msk >> dy;
                        if(dy && i - dx - 1 >= 0) {
                            // printf("add %d: %llu\n", i - dx - 1, msk << (64 - dy));
                            vals[i - dx - 1] |= msk << (64 - dy);
                        }
                    }
                } else {
                    if(i + dx < blen) {
                        vals[i + dx] |= msk << dy;
                        // printf("add %d: %llu\n", i + dx, msk << dy);
                        if(dy && i + dx + 1 < blen) {
                            // printf("add %d: %llu\n", i + dx + 1, msk >> (64 - dy));
                            vals[i + dx + 1] |= msk >> (64 - dy);
                        }
                    }
                }
            }
            // if(len < (blen << 6))
            //     vals[blen - 1] &= ~0ull >> ((blen << 6) - len);
            // src.print();
            // print();
        }
        void print() const {
            for(int i = 0; i < len; ++i)
                printf("%d", test(i));
            puts("");
        }
    };
public:
    bool possiblyEquals(string s1, string s2) {
        int n = s1.length(), m = s2.length();
        vector<int> typ1(n), typ2(m);
        for(int i = 0; i < n; ++i)
            typ1[i] = s1[i] >= '0' && s1[i] <= '9';
        for(int i = 0; i < m; ++i)
            typ2[i] = s2[i] >= '0' && s2[i] <= '9';
        int upp1 = 1000, upp2 = 1000;
        // for(int i = 0; i < n; ++i) {
        //     if(!typ1[i])
        //         continue;
        //     int val = 0;
        //     for( ; i < n && typ1[i]; ++i)
        //         val = val * 10 + (s1[i] - '0');
        //     upp1 += val;
        // }
        // for(int i = 0; i < m; ++i) {
        //     if(!typ2[i])
        //         continue;
        //     int val = 0;
        //     for( ; i < m && typ2[i]; ++i)
        //         val = val * 10 + (s2[i] - '0');
        //     upp2 += val;
        // }
        // printf("upp1 %d upp2 %d\n", upp1, upp2);
        int len = upp1 + upp2 + 1;
        vector<vector<Bitset> > dp(n + 1, vector<Bitset>(m + 1)); // [-upp1, upp2]
        for(int i = 0; i <= n; ++i)
            for(int j = 0; j <= m; ++j)
                dp[i][j].init(len);
        dp[0][0].set(upp1);
        for(int i = 0; i <= n; ++i)
            for(int j = 0; j <= m; ++j) {
                // add/sub num
                for(int k = i, adt = 0; k < n && typ1[k]; ++k) {
                    adt = adt * 10 + (s1[k] - '0');
                    // printf("%d %d -> %d %d: ", i, j, k + 1, j);
                    dp[k + 1][j].trans(dp[i][j], 0, len, -adt);
                }
                for(int k = j, adt = 0; k < m && typ2[k]; ++k) {
                    adt = adt * 10 + (s2[k] - '0');
                    // printf("%d %d -> %d %d: ", i, j, i, k + 1);
                    dp[i][k + 1].trans(dp[i][j], 0, len, adt);
                }
                // num == ch, num first
                if(i < n && !typ1[i]) {
                    // printf("%d %d -> %d %d: ", i, j, i + 1, j);
                    dp[i + 1][j].trans(dp[i][j], upp1 + 1, len, -1);
                }
                if(j < m && !typ2[j]) {
                    // printf("%d %d -> %d %d: ", i, j, i, j + 1);
                    dp[i][j + 1].trans(dp[i][j], 0, upp1, 1);
                }
                // ch == ch
                if(i < n && j < m && s1[i] == s2[j]) {
                    // printf("%d %d -> %d %d: ", i, j, i + 1, j + 1);
                    // dp[i + 1][j + 1].trans(dp[i][j], 0, len, 0);
                    if(dp[i][j].test(upp1))
                        dp[i + 1][j + 1].set(upp1);
                }
            }
        // for(int i = 0; i <= n; ++i)
        //     for(int j = 0; j <= m; ++j)
        //         for(int x = 0; x <= upp1 + upp2; ++x)
        //             if(dp[i][j].test(x))
        //                 printf("%d %d %d\n", i, j, x - upp1);
        // puts("");
        return dp[n][m].test(upp1);
    }
};
