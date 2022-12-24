#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 501, maxd = 8, maxs = 1 << maxd | 1, mod = (int)1e9 + 7;
int tot, pr[maxn], d[maxn];
int t, n, m, sz, all, tr[maxs], f[3][maxn][maxs];
vector<int> s[maxn];
inline void mod_inc(int &x, int y) {
    (x += y) >= mod && (x -= mod);
}
int main() {
    for(int i = 2; i < maxn; ++i) {
        if(!d[i])
            pr[tot++] = d[i] = i;
        for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
            d[k] = pr[j];
            if(d[i] == pr[j])
                break;
        }
    }
    pr[tot] = maxn;
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        for(sz = 0; pr[sz] * pr[sz] <= n; ++sz);
        all = 1 << sz;
        for(int i = 1; i <= n; ++i) {
            vector<int>().swap(s[i]);
            int val = i, mask = 0;
            for(int j = 0; j < sz && val > 1; ++j) {
                int cnt = 0;
                for( ; d[val] == pr[j]; val /= pr[j], ++cnt);
                if(cnt > 1) {
                    mask = -1;
                    break;
                }
                mask += cnt << j;
            }
            if(mask >= 0)
                s[val].push_back(mask);
        }
        for(int i = 0; i <= m; ++i) {
            memset(f[0][i], 0, all * sizeof(int));
            memset(f[1][i], 0, all * sizeof(int));
        }
        int lim = 0;
        f[0][0][0] = 1;
        for(int i = 1; i <= n; ++i) {
            if(!s[i].size())
                continue;
            for(vector<int>::iterator it = s[i].begin(); it != s[i].end(); ++it) {
                int mask = *it, o = i > 1;
                // fprintf(stderr, "mask %d\n", mask);
                for(int j = 0; j < all; ++j) {
                    int nxt = mask | j;
                    for(int k = 0; k < sz; ++k)
                        if(((mask >> k) & 1) && ((j >> k) & 1)) {
                            nxt = -1;
                            break;
                        }
                    // fprintf(stderr, "tr %d : %d\n", j, nxt);
                    tr[j] = nxt;
                }
                lim < m && (++lim);
                for(int j = lim; j > 0; --j)
                    for(int k = 0; k < all; ++k)
                        if(tr[k] >= 0)
                            mod_inc(f[o][j][tr[k]], f[0][j - 1][k]);
                /*static int ccc = 0;
                ++ccc;
                for(int j = 0; j <= lim; ++j)
                    for(int k = 0; k < all; ++k)
                        if(f[0][j][k])
                            fprintf(stderr, "%d %d %d %d : %d\n", ccc, 0, j, k, f[0][j][k]);
                for(int j = 0; j <= lim; ++j)
                    for(int k = 0; k < all; ++k)
                        if(f[1][j][k])
                            fprintf(stderr, "%d %d %d %d : %d\n", ccc, 1, j, k, f[1][j][k]);*/
            }
            for(int j = 0; j <= lim; ++j)
                for(int k = 0; k < all; ++k) {
                    mod_inc(f[0][j][k], f[1][j][k]);
                    f[1][j][k] = 0;
                }
            /* fputs("conv\n", stderr);
            for(int j = 0; j <= lim; ++j)
                for(int k = 0; k < all; ++k)
                    if(f[0][j][k])
                        fprintf(stderr, "%d %d %d : %d\n", 0, j, k, f[0][j][k]);*/
        }
        int ans = 0;
        for(int i = 1; i <= lim; ++i)
            for(int j = 0; j < all; ++j)
                mod_inc(ans, f[0][i][j]);
        printf("%d\n", ans);
    }
    return 0;
}