#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 401, maxm = 200001, mod = 998244353;
int fact[maxm], iact[maxm];
int n, dsu[maxn], deg[maxn], tmp[maxn], e[maxn][maxn];
inline int mod_inv(int x) {
    return x <= 1 ? x : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
int dsu_find(int x) {
    return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
void dsu_merge(int u, int v) {
    u = dsu_find(u);
    v = dsu_find(v);
    if(u == v)
        return;
    if(dsu[u] < dsu[v])
        swap(u, v);
    if(dsu[u] == dsu[v])
        --dsu[v];
    dsu[u] = v;
}
int main() {
    iact[1] = 1;
    for(int i = 2; i < maxm; ++i)
        iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
    fact[0] = iact[0] = 1;
    for(int i = 1; i < maxm; ++i) {
        fact[i] = (LL)fact[i - 1] * i % mod;
        iact[i] = (LL)iact[i - 1] * iact[i] % mod;
    }
    for(int Case = 1; scanf("%d", &n) == 1; ++Case) {
        memset(dsu, -1, n * sizeof(int));
        memset(deg, 0, n * sizeof(int));
        memset(tmp, 0, n * sizeof(int));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j) {
                scanf("%d", e[i] + j);
                deg[i] += e[i][j];
                tmp[j] += e[i][j];
                if(e[i][j])
                    dsu_merge(i, j);
            }
        bool chk = 1;
        for(int i = 0; i < n && chk; ++i)
            chk &= dsu_find(i) == dsu_find(0) && deg[i] == tmp[i];
        if(!chk) {
            printf("Case #%d: 0\n", Case);
            continue;
        }
        int ans = deg[0];
        for(int i = 0; i < n; ++i) {
            ans = (LL)ans * fact[deg[i] - 1] % mod;
            for(int j = 0; j < n; ++j) {
                if(!e[i][j])
                    continue;
                ans = (LL)ans * iact[e[i][j]] % mod;
                e[i][j] = mod - e[i][j];
            }
            (e[i][i] += deg[i]) >= mod && (e[i][i] -= mod);
        }
        for(int i = 1; i < n; ++i) {
            int k = -1;
            for(int j = i; j < n; ++j)
                if(e[j][i]) {
                    k = j;
                    break;
                }
            if(k == -1) {
                ans = 0;
                break;
            }
            for(int j = i; j < n; ++j)
                swap(e[k][j], e[i][j]);
            ans = (LL)ans * e[i][i] % mod;
            int invd = mod_inv(e[i][i]);
            for(int j = i; j < n; ++j)
                e[i][j] = (LL)e[i][j] * invd % mod;
            for(int j = i + 1; j < n; ++j)
                if(e[j][i]) {
                    int coe = mod - e[j][i];
                    for(int k = i; k < n; ++k)
                        e[j][k] = (e[j][k] + (LL)coe * e[i][k]) % mod;
                }
        }
        printf("Case #%d: %d\n", Case, ans);
    }
    return 0;
}
