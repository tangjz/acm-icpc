#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 50001, maxm = 201, mod = 998244353;
int t, n, m, len, sz[maxn], f[maxn][maxm], g[maxn][maxm], h[2][maxm];
vector<int> e[maxn];
inline int mod_add(int x, int y) {
    return (x += y) < mod ? x : x - mod;
}
inline int mod_sub(int x, int y) {
    return (x -= y) < 0 ? x + mod : x;
}
void merge(int fsz, int f0[], int f1[], int gsz, int g0[], int g1[]) {
    int sz = min(fsz + gsz + 1, m);
    memcpy(h[0], f0, (fsz + 1) * sizeof(int));
    memset(f0, 0, sz * sizeof(int));
    memcpy(h[1], f1, (fsz + 1) * sizeof(int));
    memset(f1, 0, sz * sizeof(int));
    for(int i = 0; i <= fsz; ++i) {
        if(h[0][i])
            for(int j = 0, k = i; j <= gsz; ++j, (++k) == m && (k = 0)) {
                if(g0[j]) {
                    int tmp = (LL)h[0][i] * g0[j] % mod;
                    f0[k] = mod_add(f0[k], tmp);
                    f1[(k + 1) % m] = mod_add(f1[(k + 1) % m], tmp);
                }
                if(g1[j]) {
                    int tmp = 2LL * h[0][i] * g1[j] % mod;
                    f0[k] = mod_add(f0[k], tmp);
                }
            }
        if(h[1][i])
            for(int j = 0, k = i; j <= gsz; ++j, (++k) == m && (k = 0)) {
                if(g0[j] + g1[j]) {
                    int tmp = 2LL * h[1][i] * (g0[j] + g1[j]) % mod;
                    f1[k] = mod_add(f1[k], tmp);
                }
            }
    }
}
void dfs(int u, int fa) {
    sz[u] = min(1, m - 1);
    f[u][0] = 1;
    f[u][1] = g[u][0] = g[u][1] = 0;
    for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
        int v = *it;
        if(v == fa)
            continue;
        dfs(v, u);
        merge(sz[u], f[u], g[u], sz[v], f[v], g[v]);
        sz[u] = min(sz[u] + sz[v], m - 1);
    }
}
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        for(len = 1; len < m << 1; len <<= 1);
        for(int i = 1; i <= n; ++i)
            vector<int>().swap(e[i]);
        for(int i = 1; i < n; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            e[u].push_back(v);
            e[v].push_back(u);
        }
        dfs(1, -1);
        printf("%d\n", mod_add(f[1][0], g[1][0]));
    }
    return 0;
}
