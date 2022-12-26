#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100001, maxd = 7;
int tot, pr[maxn], d[maxn], cnt, p[maxd], c[maxd];
int n, a[maxn], f[maxn], ans[maxn];
vector<int> e[maxn];
void upd(int dep, int val)
{
    if(dep == cnt)
    {
        ++f[val];
        return;
    }
    upd(dep + 1, val);
    for(int i = 0; i < c[dep]; ++i)
        upd(dep + 1, val *= p[dep]);
}
int que(int dep, int val)
{
    return dep == cnt ? f[val] : que(dep + 1, val) - que(dep + 1, val * p[dep]);
}
void dfs(int u, int fa)
{
    cnt = 0;
    for(int tmp = a[u]; tmp > 1; ++cnt)
        for(p[cnt] = d[tmp], c[cnt] = 0; d[tmp] == p[cnt]; tmp /= p[cnt], ++c[cnt]);
    ans[u] = -que(0, 1);
    upd(0, 1);
    for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
        if(*it != fa)
            dfs(*it, u);
    cnt = 0;
    for(int tmp = a[u]; tmp > 1; ++cnt)
        for(p[cnt] = d[tmp]; d[tmp] == p[cnt]; tmp /= p[cnt]);
    ans[u] += que(0, 1);
}
int main()
{
    for(int i = 2; i < maxn; ++i)
    {
        if(!d[i])
            pr[tot++] = d[i] = i;
        for(int j = 0, k; (k = i * pr[j]) < maxn; ++j)
        {
            d[k] = pr[j];
            if(d[i] == pr[j])
                break;
        }
    }
    for(int Case = 1; scanf("%d", &n) == 1; ++Case)
    {
        memset(f, 0, sizeof f);
        for(int i = 1; i <= n; ++i)
            vector<int>().swap(e[i]);
        for(int i = 1, u, v; i < n; ++i)
        {
            scanf("%d%d", &u, &v);
            e[u].push_back(v);
            e[v].push_back(u);
        }
        for(int i = 1; i <= n; ++i)
            scanf("%d", a + i);
        dfs(1, -1);
        printf("Case #%d:", Case);
        for(int i = 1; i <= n; ++i)
            printf(" %d", ans[i]);
        putchar('\n');
    }
    return 0;
}
