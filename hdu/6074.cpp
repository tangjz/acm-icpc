#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100001, maxd = 17;
int t, n, m, dep[maxn], fa[maxd][maxn];
vector<int> e[maxn];
int dsu1[maxn], idx[maxn];
int dsu2[maxn], sz[maxn];
LL sum[maxn];
struct Query {
    int a, b, c, d, w;
    bool operator < (Query const &t) const {
        return w < t.w;
    }
} que[maxn];
void dfs(int u) {
    for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
        int v = *it;
        if(v == fa[0][u])
            continue;
        dep[v] = dep[u] + 1;
        fa[0][v] = u;
        dfs(v);
    }
}
int lca(int u, int v) {
    for(int i = 0, j = dep[u] - dep[v]; j > 0; ++i, j >>= 1)
        (j & 1) && (u = fa[i][u]);
    for(int i = 0, j = dep[v] - dep[u]; j > 0; ++i, j >>= 1)
        (j & 1) && (v = fa[i][v]);
    if(u == v)
        return u;
    for(int i = maxd - 1; i >= 0; --i)
        if(fa[i][u] != fa[i][v]) {
            u = fa[i][u];
            v = fa[i][v];
        }
    return fa[0][u];
}
int dsu1_find(int x) {
    return dsu1[x] < 0 ? x : (dsu1[x] = dsu1_find(dsu1[x]));
}
void dsu1_merge(int u, int v) { // merge u -> v
    u = dsu1_find(u);
    v = dsu1_find(v);
    if(u == v)
        return;
    if(dsu1[u] == dsu1[v]) {
        --dsu1[v];
        dsu1[u] = v;
    } else if(dsu1[u] < dsu1[v]) {
        dsu1[v] = u;
        idx[u] = idx[v];
    } else {
        dsu1[u] = v;
    }
}
int dsu2_find(int x) {
    return dsu2[x] < 0 ? x : (dsu2[x] = dsu2_find(dsu2[x]));
}
void dsu2_merge(int u, int v, int w) {
    u = dsu2_find(u);
    v = dsu2_find(v);
    if(u == v)
        return;
    if(dsu2[u] == dsu2[v]) {
        --dsu2[v];
        dsu2[u] = v;
        sz[v] += sz[u];
        sum[v] += sum[u] + w;
    } else if(dsu2[u] < dsu2[v]) {
        dsu2[v] = u;
        sz[u] += sz[v];
        sum[u] += sum[v] + w;
    } else {
        dsu2[u] = v;
        sz[v] += sz[u];
        sum[v] += sum[u] + w;
    }
}
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i) {
            vector<int>().swap(e[i]);
            dsu1[i] = dsu2[i] = -1;
            idx[i] = i;
            sz[i] = 1;
            sum[i] = 0;
        }
        for(int i = 1; i < n; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            e[u].push_back(v);
            e[v].push_back(u);
        }
        for(int i = 0; i < m; ++i) {
            int &a = que[i].a, &b = que[i].b, &c = que[i].c, &d = que[i].d, &w = que[i].w;
            scanf("%d%d%d%d%d", &a, &b, &c, &d, &w);
        }
        sort(que, que + m);
        dep[1] = fa[0][1] = 0;
        dfs(1);
        for(int i = 1; i < maxd; ++i)
            for(int j = 1; j <= n; ++j)
                fa[i][j] = fa[i - 1][fa[i - 1][j]];
        for(int i = 0; i < m; ++i) {
            int &a = que[i].a, &b = que[i].b, &c = que[i].c, &d = que[i].d, &w = que[i].w;
            int pp = lca(a, b), qq = lca(c, d);
            for(int j = idx[dsu1_find(a)]; dep[pp] < dep[j]; j = idx[dsu1_find(j)]) {
                dsu1_merge(j, fa[0][j]);
                dsu2_merge(j, fa[0][j], w);
            }
            for(int j = idx[dsu1_find(b)]; dep[pp] < dep[j]; j = idx[dsu1_find(j)]) {
                dsu1_merge(j, fa[0][j]);
                dsu2_merge(j, fa[0][j], w);
            }
            for(int j = idx[dsu1_find(c)]; dep[qq] < dep[j]; j = idx[dsu1_find(j)]) {
                dsu1_merge(j, fa[0][j]);
                dsu2_merge(j, fa[0][j], w);
            }
            for(int j = idx[dsu1_find(d)]; dep[qq] < dep[j]; j = idx[dsu1_find(j)]) {
                dsu1_merge(j, fa[0][j]);
                dsu2_merge(j, fa[0][j], w);
            }
            dsu2_merge(pp, qq, w);
        }
        int mx = 0;
        LL ans = 0;
        for(int i = 1; i <= n; ++i)
            if(dsu2_find(i) == i) {
                if(mx < sz[i]) {
                    mx = sz[i];
                    ans = sum[i];
                } else if(mx == sz[i] && sum[i] < ans) {
                    ans = sum[i];
                }
            }
        printf("%d %I64d\n", mx, ans);
    }
    return 0;
}