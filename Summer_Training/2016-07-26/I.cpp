#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 50001, maxd = 16;
int n, m, q, tot, val[maxn], sz, lpos[maxn];
LL sum, ans[maxn];
std::vector<std::pair<int, int> > e[maxn];
struct Trie
{
    int cnt, ch[2];
} p[maxn * maxd];
struct Query
{
    int id, l, r;
    bool operator < (const Query &t) const
    {
        if(lpos[l] != lpos[t.l])
            return lpos[l] < lpos[t.l];
        return r < t.r;
    }
} query[maxn];
void dfs(int u)
{
    for(std::vector<std::pair<int, int> >::iterator it = e[u].begin(); it != e[u].end(); ++it)
    {
        int v = it -> first, w = it -> second;
        if(val[v] == -1)
        {
            val[v] = val[u] ^ w;
            dfs(v);
        }
    }
}
void ins(int val)
{
    int rt = 0;
    for(int i = maxd - 1; i >= 0; --i)
    {
        int o = (val >> i) & 1;
        if(!p[rt].ch[o])
        {
            p[rt].ch[o] = tot;
            memset(p + (tot++), 0, sizeof p[0]);
        }
        rt = p[rt].ch[o];
    }
}
void upd(int val, int c)
{
    int rt = 0;
    for(int i = maxd - 1; i >= 0; --i)
    {
        int o = (val >> i) & 1;
        rt = p[rt].ch[o];
        p[rt].cnt += c;
    }
}
int que(int val)
{
    int rt = 0, ret = 0;
    //printf("query %d :\n", val);
    for(int i = maxd - 1; i >= 0; --i)
    {
        int o1 = (val >> i) & 1, o2 = (m >> i) & 1;
        if(!o2 && p[rt].ch[o1 ^ 1])
        {
            ret += p[p[rt].ch[o1 ^ 1]].cnt;
            //printf("diff %d : %d\n", i, p[p[rt].ch[o1 ^ 1]].cnt);
        }
        if(!p[rt].ch[o1 ^ o2])
            break;
        rt = p[rt].ch[o1 ^ o2];
    }
    return ret;
}
int main()
{
    while(scanf("%d%d%d", &n, &m, &q) == 3)
    {
        // calc value
        memset(val, -1, sizeof val);
        for(int i = 1; i <= n; ++i)
            std::vector<std::pair<int, int> >().swap(e[i]);
        for(int i = 1; i < n; ++i)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            e[u].push_back(std::make_pair(v, w));
            e[v].push_back(std::make_pair(u, w));
        }
        val[1] = 0;
        dfs(1);
        // build trie
        tot = 0;
        memset(p + (tot++), 0, sizeof p[0]);
        for(int i = 1; i <= n; ++i)
            ins(val[i]);
        // mo's algorithm
        sz = (int)ceil(sqrt(n));
        for(int i = 1, j = 1; i <= n; ++i, (i % sz == 1 ? ++j : 0))
            lpos[i] = j;
        for(int i = 1; i <= q; ++i)
        {
            query[i].id = i;
            scanf("%d%d", &query[i].l, &query[i].r);
        }
        std::sort(query + 1, query + q + 1);
        sum = 0;
        for(int i = 1, qL = 1, qR = 0; i <= q; ++i)
        {
            for( ; qR < query[i].r; ++qR)
            {
                //printf("R : %d -> %d\n", qR, qR + 1);
                sum += que(val[qR + 1]);
                upd(val[qR + 1], 1);
            }
            for( ; qL > query[i].l; --qL)
            {
                //printf("L : %d -> %d\n", qL, qL - 1);
                sum += que(val[qL - 1]);
                upd(val[qL - 1], 1);
            }
            for( ; qL < query[i].l; ++qL)
            {
                //printf("L : %d -> %d\n", qL, qL + 1);
                upd(val[qL], -1);
                sum -= que(val[qL]);
            }
            for( ; qR > query[i].r; --qR)
            {
                //printf("R : %d -> %d\n", qR, qR - 1);
                upd(val[qR], -1);
                sum -= que(val[qR]);
            }
            ans[query[i].id] = sum;
        }
        for(int i = 1; i <= q; ++i)
            printf("%d\n", ans[i]);
    }
    return 0;
}
