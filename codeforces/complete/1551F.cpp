#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LD;
const int maxn = (int)1e2 + 9, maxm = (int)1e6 + 9;
const int mod = (int)1e9 + 7;
const DB eps = (DB)1e-12, pi = acos((DB)-1);

inline int sgn(DB x) {
    return (x > eps) - (x < -eps);
}

int n, m, ans;
int f[maxn][maxn], g[maxn][maxn]; // f: down, g: all
vector<int> e[maxn];

void dfs1(int u, int p) {
    memset(f[u], 0, n * sizeof(int));
    ++f[u][0];
    for(int v: e[u]) {
        if(v == p)
            continue;
        dfs1(v, u);
        for(int i = 0; i + 1 < n; ++i)
            f[u][i + 1] += f[v][i];
    }
    // printf("down %d:", u);
    // for(int i = 0; i < n && f[u][i]; ++i)
    //     printf(" %d", f[u][i]);
    // puts("");
}

void dfs2(int u, int p) {
    // printf("all %d:", u);
    // for(int i = 0; i < n && g[u][i]; ++i)
    //     printf(" %d", g[u][i]);
    // puts("");
    for(int v: e[u]) {
        if(v == p)
            continue;
        memcpy(g[v], f[v], n * sizeof(int));
        for(int i = 0; i < n; ++i)
            g[v][i + 1] += g[u][i] - (i > 0 ? f[v][i - 1] : 0);
        dfs2(v, u);
    }
    static int up[maxn], dp[maxn][maxn];
    memcpy(up, g[u], n * sizeof(int));
    for(int i = 0; i < n; ++i) {
        dp[i][0] = 1;
        memset(dp[i] + 1, 0, m * sizeof(int));
    }
    for(int v: e[u]) {
        if(v == p)
            continue;
        for(int i = 0; i < n; ++i) {
            if(i + 1 < n)
                up[i + 1] -= f[v][i];
            if(f[v][i])
                for(int j = m; j > 0; --j)
                    dp[i][j] = (dp[i][j] + (LL)dp[i][j - 1] * f[v][i]) % mod;
        }
    }
    // printf("up %d:", u);
    // for(int i = 0; i < n && up[i]; ++i)
    //     printf(" %d", up[i]);
    // puts("");
    // printf("dp %d:\n", u);
    for(int i = 0; i < n; ++i) {
        if(i + 1 < n && up[i + 1])
            for(int j = m; j > 0; --j)
                dp[i][j] = (dp[i][j] + (LL)dp[i][j - 1] * up[i + 1]) % mod;
        // printf("dis %d:", i + 1);
        // for(int j = 0; j <= m; ++j)
        //     printf(" %d", dp[i][j]);
        // puts("");
        ans = (ans + dp[i][m]) % mod;
    }
}

void solve() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    if(m == 2) {
        printf("%d\n", n * (n - 1) / 2);
    } else {
        dfs1(1, -1);
        ans = 0;
        memcpy(g[1], f[1], n * sizeof(int));
        dfs2(1, -1);
        printf("%d\n", ans);
    }
    for(int i = 1; i <= n; ++i)
        vector<int>().swap(e[i]);
}

int main() {
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        // printf("Case #%d: %d\n", Case, solve());
        solve();
    }
    return 0;
}