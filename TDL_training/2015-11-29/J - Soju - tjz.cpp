#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 200001, INF = 0x3f3f3f3f;
int t, n, m, tot, ans;
struct Point
{
	int typ, x, y;
	bool operator < (const Point &t) const
	{
		return y < t.y;
	}
} a[maxn];
void upd(int &x, int y)
{
	if(x > y)
		x = y;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		tot = 0;
		ans = INF;
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
		{
			scanf("%d%d", &a[tot].x, &a[tot].y);
			a[tot++].typ = 0;
		}
		scanf("%d", &m);
		for(int i = 0; i < m; ++i)
		{
			scanf("%d%d", &a[tot].x, &a[tot].y);
			a[tot++].typ = 1;
		}
		sort(a, a + tot);
		for(int i = 0, j = INF; i < tot; ++i)
			if(a[i].typ)
				upd(j, a[i].x - a[i].y);
			else if(j != INF)
				upd(ans, j - a[i].x + a[i].y);
		for(int i = tot - 1, j = INF; i >= 0; --i)
			if(a[i].typ)
				upd(j, a[i].x + a[i].y);
			else if(j != INF)
				upd(ans, j - a[i].x - a[i].y);
		printf("%d\n", ans);
	}
	return 0;
}
