#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010, maxd = 17;
typedef pair<int, int> Edge;
int n, m, tot, bit[maxn << 1], in[maxn], out[maxn], dep[maxn], fa[maxn][maxd];
vector<Edge> e[maxn];
void add(int x, int v)
{
    for( ; x <= tot; x += x & -x)
        bit[x] += v;
}
int sum(int x)
{
    int ret = 0;
    for( ; x > 0; x -= x & -x)
        ret += bit[x];
    return ret;
}
void dfs(int u)
{
    in[u] = ++tot;
    for(vector<Edge>::iterator it = e[u].begin(); it != e[u].end(); ++it)
    {
        int &v = it -> first, &w = it -> second;
        if(v == fa[u][0])
            continue;
        dep[v] = dep[u] + 1;
        fa[v][0] = u;
        for(int i = 1; i < maxd; ++i)
            if(fa[v][i - 1])
                fa[v][i] = fa[fa[v][i - 1]][i - 1];
            else
                break;
        dfs(v);
    }
    out[u] = ++tot;
}
int lca(int u, int v)
{
    if(dep[u] > dep[v])
        swap(u, v);
    for(int i = 0, j = dep[v] - dep[u]; i < maxd && j; ++i, j >>= 1)
        if(j & 1)
            v = fa[v][i];
    if(u == v)
        return u;
    for(int i = maxd - 1; i >= 0; --i)
        if(fa[u][i] != fa[v][i])
        {
            u = fa[u][i];
            v = fa[v][i];
        }
    return fa[u][0];
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(make_pair(v, 1));
        e[v].push_back(make_pair(u, -1));
    }
    dfs(1);
    for(int i = 1; i <= n; ++i)
        for(vector<Edge>::iterator it = e[i].begin(); it != e[i].end(); ++it)
        {
            int &v = it -> first, &w = it -> second;
            if(v == fa[i][0])
                continue;
            add(in[v], w);
            add(out[v], -w);
        }
    scanf("%d", &m);
    while(m--)
    {
        int x, y, pp;
        scanf("%d%d", &x, &y);
        pp = lca(x, y);
        if(sum(in[x]) - sum(in[pp]) == dep[pp] - dep[x]
        && sum(in[y]) - sum(in[pp]) == dep[y] - dep[pp])
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}
