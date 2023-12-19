class Solution {
public:
    int maximumStrongPairXor(vector<int>& A) {
        static const int maxs = (int)1e6 + 9;
        static int nxt[2][maxs] = {}, ctr[maxs] = {};
        int mx = 0, tot = 0;
        sort(A.begin(), A.end());
        A.erase(unique(A.begin(), A.end()), A.end());
        for( ; 1 << mx <= A.back(); ++mx);
        auto clr = [&](int i) {
            nxt[0][i] = nxt[1][i] = ctr[i] = 0;
        };
        clr(0);
        auto upd = [&](int x, int v) {
            int rt = 0;
            ctr[rt] += v;
            for(int i = mx - 1; i >= 0; --i) {
                int o = (x >> i) & 1;
                if(!nxt[o][rt]) {
                    nxt[o][rt] = ++tot;
                    clr(tot);
                }
                // printf("%d", o);
                rt = nxt[o][rt];
                ctr[rt] += v;
            }
            // puts("");
            // printf("upd %d %d: %d\n", x, v, tot);
        };
        auto ask = [&](int x) {
            int rt = 0, ret = 0;
            assert(ctr[rt]);
            for(int i = mx - 1; i >= 0; --i) {
                int o = !((x >> i) & 1);
                if(!nxt[o][rt] || !ctr[nxt[o][rt]]) {
                    o = !o;
                } else {
                    ret |= 1 << i;
                }
                // printf("%d", o);
                rt = nxt[o][rt];
                // assert(ctr[rt]);
            }
            // puts("");
            // printf("ask %d: %d\n", x, ret);
            return ret;
        };
        int n = A.size(), ans = 0;
        for(int i = 0, j = 0; i < n; ++i) {
            for( ; j < i && A[j] + A[j] < A[i]; upd(A[j++], -1));
            upd(A[i], 1);
            ans = max(ans, ask(A[i]));
        }
        // puts("");
        return ans;
    }
};
