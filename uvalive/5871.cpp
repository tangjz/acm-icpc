#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 500001;
int t, n, tot, que[maxn << 1], bit[maxn << 1], vis[maxn << 1], cnt, ans[maxn];
struct Point
{
	int id, typ, x, y;
} a[maxn];
bool cmp1(const Point &a, const Point &b)
{
	return a.id < b.id;
}
bool cmp2(const Point &a, const Point &b)
{
	if(a.x != b.x)
		return a.x < b.x;
	if(a.y != b.y)
		return a.y > b.y;
	return a.id < b.id;
}
void add(int x, int v)
{
	for( ; x > 0; x -= x & -x)
		if(vis[x] == t)
			bit[x] += v;
		else
		{
			vis[x] = t;
			bit[x] = v;
		}
}
int sum(int x)
{
	int ret = 0;
	for( ; x <= tot; x += x & -x)
		if(vis[x] == t)
			ret += bit[x];
	return ret;
}
void solve(int L, int R)
{
	if(L == R)
		return;
	int M = L + R >> 1;
	solve(L, M);
	solve(M + 1, R);
	sort(a + L, a + R + 1, cmp2);
	++t;
	for(int i = L; i <= R; ++i)
		if(a[i].id <= M && !a[i].typ)
			add(a[i].y, 1);
		else if(a[i].id > M && a[i].typ)
			ans[a[i].typ] += sum(a[i].y);// >= a[i].y
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		tot = t = cnt = 0;
		for(int i = 1; i <= n; ++i)
		{
			int L, R;
			char op[2];
			scanf("%s%d%d", op, &L, &R);
			que[tot++] = L;
			que[tot++] = R;
			if(op[0] == '+')
				a[i] = (Point){i, 0, L, R};
			else
				a[i] = (Point){i, ++cnt, L, R};
		}
		sort(que, que + tot);
		tot = unique(que, que + tot) - que;
		for(int i = 1; i <= n; ++i)
		{
			a[i].x = lower_bound(que, que + tot, a[i].x) - que + 1;
			a[i].y = lower_bound(que, que + tot, a[i].y) - que + 1;
		}
		for(int i = 1; i <= cnt; ++i)
			ans[i] = 0;
		solve(1, n);
		for(int i = 1; i <= cnt; ++i)
			printf("%d\n", ans[i]);
	}
	return 0;
}
