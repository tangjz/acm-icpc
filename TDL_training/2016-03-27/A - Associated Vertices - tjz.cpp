#include <bitset>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 10001;
int n, m, seq[maxn], scnt, sno[maxn], sw[maxn], ans;
bool vis[maxn];
vector<int> e1[maxn], r1[maxn], e2[maxn], r2[maxn];
bitset<maxn> f[maxn];
void pfs1(int u)
{
    vis[u] = 1;
    for(vector<int>::iterator it = e1[u].begin(); it != e1[u].end(); ++it)
        if(!vis[*it])
            pfs1(*it);
    seq[scnt++] = u;
}
void pfs2(int u)
{
    vis[u] = 1;
    sno[u] = scnt;
    ++sw[scnt];
    for(vector<int>::iterator it = r1[u].begin(); it != r1[u].end(); ++it)
        if(!vis[*it])
            pfs2(*it);
}
void dfs1(int u)
{
    vis[u] = 1;
    for(vector<int>::iterator it = e2[u].begin(); it != e2[u].end(); ++it)
    {
        int v = *it;
        if(!vis[v])
            dfs1(v);
        f[u] |= f[v];
    }
}
void dfs2(int u)
{
    vis[u] = 1;
    for(vector<int>::iterator it = r2[u].begin(); it != r2[u].end(); ++it)
    {
        int v = *it;
        if(!vis[v])
            dfs2(v);
        f[u] |= f[v];
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    while(m--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        --u;
        --v;
        e1[u].push_back(v);
        r1[v].push_back(u);
    }
    scnt = 0;
    memset(vis, 0, n * sizeof(bool));
    for(int i = 0; i < n; ++i)
        if(!vis[i])
            pfs1(i);
    scnt = 0;
    memset(vis, 0, n * sizeof(bool));
    for(int i = n - 1; i >= 0; --i)
        if(!vis[seq[i]])
        {
            pfs2(seq[i]);
            ++scnt;
        }
    for(int i = 0; i < n; ++i)
    {
        f[sno[i]].set(i);
        for(vector<int>::iterator it = e1[i].begin(); it != e1[i].end(); ++it)
        {
            f[sno[i]].set(*it);
            e2[sno[i]].push_back(sno[*it]);
        }
        for(vector<int>::iterator it = r1[i].begin(); it != r1[i].end(); ++it)
            r2[sno[i]].push_back(sno[*it]);
    }
    memset(vis, 0, scnt * sizeof(bool));
    for(int i = 0; i < scnt; ++i)
        if(!vis[i])
            dfs1(i);
    memset(vis, 0, scnt * sizeof(bool));
    for(int i = 0; i < scnt; ++i)
        if(!vis[i])
            dfs2(i);
    ans = 0;
    for(int i = 0; i < scnt; ++i)
        ans += f[i].count() * sw[i];
    printf("%d\n", ans);
    return 0;
}
