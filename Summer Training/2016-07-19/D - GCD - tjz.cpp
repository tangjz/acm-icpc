#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxn = 100010, maxm = maxn * 18;
int t, n, a[maxn], q;
struct Query
{
    int id, l, r, v;
    bool operator < (const Query &t) const
    {
        return r < t.r;
    }
} b[maxn];
int tot, cnt;
std::pair<int, int> g[maxn];
std::pair<int, LL> que[maxm];
bool cmp(const Query &a, const Query &b)
{
    return a.id < b.id;
}
int main()
{
    scanf("%d", &t);
    for(int Case = 1; Case <= t; ++Case)
    {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i)
            scanf("%d", a + i);
        scanf("%d", &q);
        for(int i = 0; i < q; ++i)
        {
            b[i].id = i;
            scanf("%d%d", &b[i].l, &b[i].r);
        }
        std::sort(b, b + q);
        tot = cnt = 0;
        for(int i = 1, j = 0; i <= n; ++i)
        {
            g[tot++] = std::make_pair(i, 0);
            for(int k = 0; k < tot; ++k)
            {
                //printf("gcd(%d, %d)", g[k].second, a[i]);
                g[k].second = std::__gcd(g[k].second, a[i]);
                //printf("=%d\n", g[k].second);
            }
            int tmp = 0;
            for(int k = 0; k < tot; ++k)
                if(!k || g[tmp - 1].second != g[k].second)
                    g[tmp++] = g[k];
            tot = tmp;
            //printf("tot : %d\n", tot);
            g[tot] = std::make_pair(i + 1, 0);
            for(int k = 0; k < tot; ++k)
            {
                //printf("gcd [%d, %d] = %d\n", g[k].first, i, g[k].second);
                que[cnt++] = std::make_pair(g[k].second, (LL)(g[k + 1].first - g[k].first));
            }
            for( ; j < q && b[j].r == i; ++j)
            {
                int idx = std::lower_bound(g, g + tot + 1, std::make_pair(b[j].l + 1, 0)) - g;
                int val =  g[idx - 1].second;
                b[j].v = val;
                //printf("query [%d, %d] = %d\n", b[j].l, b[j].r, b[j].v);
            }
        }
        std::sort(que, que + cnt);
        tot = 0;
        for(int i = 0; i < cnt; ++i)
            if(!i || que[tot - 1].first != que[i].first)
                que[tot++] = que[i];
            else
                que[tot - 1].second += que[i].second;
        cnt = tot;
        std::sort(b, b + q, cmp);
        printf("Case #%d:\n", Case);
        for(int i = 0; i < q; ++i)
        {
            int val = b[i].v;
            LL ans = std::lower_bound(que, que + cnt, std::make_pair(val, 0LL)) -> second;
            printf("%d %I64d\n", val, ans);
        }
    }
    return 0;
}
