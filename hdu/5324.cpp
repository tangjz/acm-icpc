#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 50010;
int n, tt, tot, f[maxn], p[maxn], vis[maxn], bit[maxn], ans[maxn];
struct Point
{
	int id, L, R;
	bool operator < (const Point &x) const
	{
		if(L != x.L)
			return L > x.L;
		if(R != x.R)
			return R < x.R;
		return id < x.id;
	}
} a[maxn];
bool cmp(const Point &x, const Point &y)
{
	return x.id < y.id;
}
void upd(int x, int v)
{
	for( ; x > 0; x -= x & -x)
	{
		if(vis[x] != tt)
		{
			vis[x] = tt;
			bit[x] = v;
			continue;
		}
		if(f[bit[x]] < f[v] || f[bit[x]] == f[v] && bit[x] > v)
			bit[x] = v;
	}
}
int que(int x)
{
	int pos = n + 1;
	for( ; x <= tot; x += x & -x)
	{
		if(vis[x] != tt)
			continue;
		if(f[pos] < f[bit[x]] || f[pos] == f[bit[x]] && pos > bit[x])
			pos = bit[x];
	}
	return pos;
}
void solve(int l, int r)
{
	if(l == r)
		return;
	int mid = l + r >> 1;
	solve(mid + 1, r);
	++tt;
	sort(a + l, a + r + 1);
	for(int i = r; i >= l; --i)
		if(a[i].id > mid)
			upd(a[i].R, a[i].id);
		else
		{
			int tmp = que(a[i].R);
			if(f[a[i].id] < f[tmp] + 1 || f[a[i].id] == f[tmp] + 1 && p[a[i].id] > tmp)
			{
				p[a[i].id] = tmp;
				f[a[i].id] = f[tmp] + 1;
			}
		}
	sort(a + l, a + r + 1, cmp);
	solve(l, mid);
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", &a[i].L);
			a[i].id = i;
			p[i] = n + 1;
			f[i] = 1;
		}
		f[n + 1] = 0;
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", &a[i].R);
			bit[i] = a[i].R;
		}
		sort(bit + 1, bit + n + 1);
		tot = unique(bit + 1, bit + n + 1) - bit - 1;
		for(int i = 1; i <= n; ++i)
			a[i].R = lower_bound(bit + 1, bit + tot + 1, a[i].R) - bit;
		solve(1, n);
		int pos = 1;
		for(int i = 2; i <= n; ++i)
			if(f[pos] < f[i])
				pos = i;
		printf("%d\n", f[pos]);
		for( ; pos <= n; pos = p[pos])
			printf("%d%c", pos, " \n"[p[pos] > n]);
	}
	return 0;
}
