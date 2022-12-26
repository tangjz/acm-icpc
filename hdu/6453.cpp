#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e4 + 1, maxm = (int)3e4 + 1, maxw = 400 * 3 + 1, mod = (int)1e9 + 7, inv6 = (mod + 1) / 6;
int inv[maxw], iact[maxw], pw[maxw][maxw];
int t, n, m, w, a[maxn], f[maxn][3][maxw], cnt[maxw], poly[maxw];
vector<int> e[maxn];
bool vis[maxn];
inline void mod_inc(int &x, int y) {
    (x += y) >= mod && (x -= mod);
}
void dfs(int u) {
    vis[u] = 1;
    int (*fu)[maxw] = f[u];
    memcpy(fu[0] + 1, pw[a[u]] + 1, w * sizeof(int));
    memcpy(fu[1] + 1, pw[a[u] * 2] + 1, w * sizeof(int));
    memcpy(fu[2] + 1, pw[a[u] * 3] + 1, w * sizeof(int));
    for(int v : e[u]) {
        if(!vis[v])
            dfs(v);
        int (*fv)[maxw] = f[v];
        for(int i = 1; i <= w; ++i) {
            mod_inc(fu[0][i], fv[0][i]);
            mod_inc(fu[1][i], fv[1][i]);
            mod_inc(fu[2][i], fv[2][i]);
        }
    }
    for(int i = 1; i <= w; ++i)
        cnt[i] = (cnt[i] + (((LL)fu[0][i] * fu[0][i] - 3LL * fu[1][i]) % mod * fu[0][i] + 2LL * fu[2][i])) % mod;
}
int main() {
    inv[1] = pw[0][0] = pw[0][1] = 1;
    for(int i = 2; i < maxw; ++i) {
        inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
        pw[0][i] = 1;
    }
    iact[0] = 1;
    for(int i = 1; i < maxw; ++i) {
        iact[i] = (LL)iact[i - 1] * inv[i] % mod;
        for(int j = 1; j < maxw; ++j)
            pw[i][j] = (LL)pw[i - 1][j] * j % mod;
    }
    scanf("%d", &t);
    for(int Case = 1; Case <= t; ++Case) {
        scanf("%d%d%d", &n, &m, &w);
        w *= 3;
        for(int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            vector<int>().swap(e[i]);
        }
        while(m--) {
            int u, v;
            scanf("%d%d", &u, &v);
            e[u].push_back(v);
        }
        memset(vis + 1, 0, n * sizeof(bool));
        memset(cnt + 1, 0, w * sizeof(int));
        for(int i = 1; i <= n; ++i)
            if(!vis[i])
                dfs(i);
        memset(poly, 0, (w + 1) * sizeof(int));
        for(int i = 1; i <= w; ++i) {
            if(!cnt[i])
                continue;
            int coeff = cnt[i] < 0 ? cnt[i] + mod : cnt[i], prd = inv[i];
            coeff = (LL)coeff * inv6 % mod * iact[i] % mod * iact[w - i] % mod;
            if(!((w - i) & 1))
                coeff = mod - coeff;
            for(int j = 0; j <= w; ++j) {
                coeff = (LL)coeff * prd % mod;
                (poly[j] += coeff) >= mod && (poly[j] -= mod);
            }
        }
        for(int i = 0; i <= w; ++i)
            for(int j = w; j >= 0; --j)
                poly[j] = ((j ? poly[j - 1] : 0) - (LL)i * poly[j]) % mod;
        printf("Case #%d: ", Case);
        for(int i = 1; i <= w; ++i)
            printf("%d%c", poly[i] < 0 ? poly[i] + mod : poly[i], " \n"[i == w]);
    }
    return 0;
}
