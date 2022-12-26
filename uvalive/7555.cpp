#include <cmath>
#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn = 100010;
typedef long long LL;
const long double pi = acos(-1.0), area[3] = {pi / 4, pi / 6 + sqrt(3.0) / 4, 1.0};
int n, m, A, q, tot;
LL cnt[3];
struct Point
{
	int x, y;
	bool operator < (const Point &t) const
	{
		return x < t.x || x == t.x && y < t.y;
	}
	bool operator == (const Point &t) const
	{
		return x == t.x && y == t.y;
	}
}p[maxn];
struct Cir
{
	int lx, ly, idx;
	bool operator < (const Cir &t) const
	{
		return lx < t.lx || lx == t.lx && ly < t.ly;
	}
} c[maxn << 2];
int main()
{
	while(scanf("%d%d%d%d", &n, &m, &A, &q) == 4)
	{
		tot = 0;
		cnt[0] = cnt[1] = cnt[2] = 0;
		for(int i = 0; i < q; ++i)
			scanf("%d%d", &p[i].x, &p[i].y);
		sort(p, p + q);
		q = unique(p, p + q) - p;
		for(int i = 0; i < q; ++i)
		{
			if(p[i].x > 0)
			{
				if(p[i].y > 0)
					c[tot++] = (Cir){p[i].x - 1, p[i].y - 1, i};
				if(p[i].y < m)
					c[tot++] = (Cir){p[i].x - 1, p[i].y, i};
			}
			if(p[i].x < n)
			{
				if(p[i].y > 0)
					c[tot++] = (Cir){p[i].x, p[i].y - 1, i};
				if(p[i].y < m)
					c[tot++] = (Cir){p[i].x, p[i].y, i};
			}
		}
		sort(c, c + tot);
		for(int i = 0, j = 0; i < tot; i = j)
		{
			int &lx = c[i].lx, &ly = c[i].ly;
			for( ; j < tot && lx == c[j].lx && ly == c[j].ly; ++j);
			int typ = i + 1 == j ? 0 : (i + 2 == j ? (p[c[i].idx].x != p[c[i + 1].idx].x && p[c[i].idx].y != p[c[i + 1].idx].y ? 2 : 1) : 2);
			cnt[typ] += (min(lx, n - A) - max(lx - A + 1, 0) + 1LL) * (min(ly, m - A) - max(ly - A + 1, 0) + 1LL);
		}
		long double ans = 0;
		for(int i = 0; i < 3; ++i)
			ans += area[i] * cnt[i];
		LL total = (n - A + 1LL) * (m - A + 1LL);
		printf("%.10f\n", (double)(ans / total));
	}
	return 0;
}
