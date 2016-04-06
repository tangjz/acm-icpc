#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100001, maxm = 11;
int n, q, m, a[maxn], b[maxn], c[maxm], p[maxn], bit[maxn], ans[maxn];
struct Query
{
	int id, l, r;
	bool operator < (const Query &t) const
	{
		return r < t.r;
	}
} query[maxn];
void upd(int x, int v)
{
	for( ; x > 0; x -= x & -x)
		if(bit[x] < v)
			bit[x] = v;
}
int que(int x)
{
	int ret = 0;
	for( ; x <= n; x += x & -x)
		if(ret < bit[x])
			ret = bit[x];
	return ret;
}
int main()
{
	scanf("%d%d%d", &n, &q, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", b + i);
		p[b[i]] = i;
	}
	for(int i = 1; i <= m; ++i)
		scanf("%d", c + i);
	for(int i = 1; i <= q; ++i)
	{
		query[i].id = i;
		scanf("%d%d", &query[i].l, &query[i].r);
	}
	sort(query + 1, query + q + 1);
	for(int i = 1, j = 1; i <= n; ++i)
	{
		for(int k = 1; k <= m; ++k)
		{
			if(b[i] - c[k] > 0 && p[b[i] - c[k]] < i)
				upd(b[i] - c[k], a[i] + a[p[b[i] - c[k]]]);
			if(b[i] + c[k] <= n && p[b[i] + c[k]] < i)
				upd(b[i] + c[k], a[i] + a[p[b[i] + c[k]]]);
		}
		for( ; j <= q && i == query[j].r; ++j)
			ans[query[j].id] = que(query[j].l);
	}
	for(int i = 1; i <= q; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
