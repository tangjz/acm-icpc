#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100001;
int n, m, tot, que[maxn], bit[maxn], ans;
struct Point
{
	int x, y, k;
} p[maxn * 3];
bool cmp1(const Point &a, const Point &b)
{
	return a.y < b.y || a.y == b.y && a.x < b.x;
}
bool cmp2(const Point &a, const Point &b)
{
	if(a.x != b.x)
		return a.x < b.x;
	if(a.k != b.k)
		return a.k < b.k;
	return a.y < b.y;
}
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
int main()
{
	scanf("%d", &n);
	ans = n;
	for(int i = 0; i < n; ++i)
	{
		scanf("%d%d", &p[i].x, &p[i].y);
		que[tot++] = p[i].y;
	}
	sort(que, que + tot);
	tot = unique(que, que + tot) - que;
	for(int i = 0; i < n; ++i)
		p[i].y = lower_bound(que, que + tot, p[i].y) - que + 1;
	sort(p, p + n, cmp1);
	for(int i = 1; i < n; ++i)
		if(p[i - 1].y == p[i].y)
		{
			p[n + (m++)] = (Point){p[i - 1].x, p[i - 1].y, 1};
			p[n + (m++)] = (Point){p[i].x, p[i].y, -1};
		}
	n += m;
	sort(p, p + n, cmp2);
	for(int i = 0; i < n; ++i)
		if(p[i].k)
			add(p[i].y, p[i].k);
		else if(i && p[i - 1].x == p[i].x && p[i - 1].k == p[i].k)
			ans += sum(p[i].y - 1) - sum(p[i - 1].y);
	printf("%d\n", ans);
	return 0;
}
