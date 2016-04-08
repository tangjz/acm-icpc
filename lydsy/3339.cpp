#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 200002;
int n, q, a[maxn], tot, hh[maxn], pos[maxn], pre[maxn], val[maxn], bit[maxn], ans[maxn];
struct Node
{
	int id, l, r;
	bool operator < (const Node &x) const
	{
		return r > x.r;
	}
} p[maxn];
int min(int x, int y)
{
	return x < y ? x : y;
}
void upd(int x, int y)
{
	for( ; x <= n; x += x & -x)
		if(bit[x] > y)
			bit[x] = y;
}
int que(int x)
{
	int ret = bit[x];
	for( ; x > 0; x -= x & -x)
		if(ret > bit[x])
			ret = bit[x];
	return ret;
}
int main()
{
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		hh[tot++] = a[i];
	}
	hh[tot++] = 0;
	sort(hh, hh + tot);
	tot = unique(hh, hh + tot) - hh;
	for(int i = 1; i <= n; ++i)
	{
		a[i] = lower_bound(hh, hh + tot, a[i]) - hh;
		pre[i] = pos[a[i]];
		pos[a[i]] = i;
	}
	for(int i = 0; i < q; ++i)
	{
		p[i].id = i;
		scanf("%d%d", &p[i].l, &p[i].r);
	}
	sort(p, p + q);
	memset(pos, 0, sizeof pos);
	for(int i = n, last = 0; i; --i)
	{
		for(pos[a[i]] = 1; pos[last] && (!last || hh[last - 1] + 1 == hh[last]); ++last);
		val[i] = last ? hh[last - 1] + 1 : 0;
	}
	memset(bit, 0x3f, sizeof bit);
	for(int i = n, j = 0; i; --i)
	{
		for( ; j < q && p[j].r == i; ++j)
			ans[p[j].id] = min(val[p[j].l], que(p[j].l));
		upd(pre[i] + 1, hh[a[i]]);
	}
	for(int i = 0; i < q; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
