class Solution {
public:
    int removeBoxes(vector<int>& boxes) {
        static const int maxn = 101;
        static int n, a[maxn], c[maxn], idx[maxn], pL[maxn];
        static int st = 0, tim[maxn][maxn][maxn], dp[maxn][maxn][maxn];

        n = 0;
        for(int x: boxes)
            if(!n || a[n - 1] != x) {
                idx[x] = -1;
                c[n] = 1;
                a[n++] = x;
            } else {
                ++c[n - 1];
            }
        for(int i = 0; i < n; ++i) {
            pL[i] = idx[a[i]];
            idx[a[i]] = i;
        }

        auto sqr = [](int x) -> int {
            return x * x;
        };
        auto upd_max = [](int &x, int y) -> bool {
            return x < y ? ((x = y), 1) : 0;
        };
        function<int(int, int, int)> calc = [&](int L, int R, int adt) {
            if(L > R)
                return 0;
            int &ret = dp[L][R][adt];
            if(tim[L][R][adt] != st) {
                tim[L][R][adt] = st;
                ret = calc(L, R - 1, 0) + sqr(adt + c[R]);
                for(int M = pL[R]; M >= L; M = pL[M])
                    upd_max(ret, calc(L, M, adt + c[R]) + calc(M + 1, R - 1, 0));
            }
            return ret;
        };
        ++st;
        return calc(0, n - 1, 0);
    }
};
