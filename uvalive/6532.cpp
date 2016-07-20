#include <set>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 10010;
int sgn(LL x)
{
	return (x > 0) - (x < 0);
}
struct Point
{
	int x, y;
	LL dot(const Point &t) const
	{
		return (LL)x * t.x + (LL)y * t.y;
	}
	LL det(const Point &t) const
	{
		return (LL)x * t.y - (LL)y * t.x;
	}
	LL mode2() const
	{
		return dot(*this);
	}
	bool operator < (const Point &t) const
	{
		if(!y && !t.y && (LL)x * t.x <= 0)
			return x > t.x;
		if(!y && x >= 0 && t.y != 0)
			return 1;
		if(!t.y && t.x >= 0 && y != 0)
			return 0;
		if((LL)t.y * y <= 0)
			return y > t.y;
		LL tmp = det(t);
		return tmp > 0;// || tmp == 0 && mode2() < t.mode2();
	}
	Point operator + (const Point &t) const
	{
		return (Point){x + t.x, y + t.y};
	}
	Point operator - (const Point &t) const
	{
		return (Point){x - t.x, y - t.y};
	}
} p[maxn], seg[maxn << 1], pp[maxn], Vec[2];
int t, n, m, ord[maxn << 1];
bool vis[maxn];
bool cmp(const int &x, const int &y)
{
	return seg[x] < seg[y];
}
bool isins(Point A1, Point A2, Point B1, Point B2)
{
	return sgn((A2 - A1).det(B1 - A1)) * sgn((A2 - A1).det(B2 - A1)) < 0
		&& sgn((B2 - B1).det(A1 - B1)) * sgn((B2 - B1).det(A2 - B1)) < 0;
}
double lineinsdist(Point A, Point B)
{
	Point u = Vec[0] - A, w = B - A;
	double t = (double)w.det(u) / Vec[1].det(w);
	return t;
}
struct cmp_sp
{
	bool operator () (const int &x, const int &y)
	{
		return lineinsdist(seg[x << 1], seg[x << 1 | 1]) < lineinsdist(seg[y << 1], seg[y << 1 | 1]);
	}
};
set<int, cmp_sp> sp;
int main()
{
	while(scanf("%d%d%d", &t, &n, &m) == 3)
	{
		for(int i = 0; i < n; ++i)
			scanf("%d%d", &p[i].x, &p[i].y);
		for(int i = 0; i < m << 1; ++i)
			scanf("%d%d", &seg[i].x, &seg[i].y);
		for(int now = 0; now < t; ++now)
		{
			int tot = 0, ans = 0;
			for(int i = 0; i < n; ++i)
				if(i != now)
					pp[tot++] = p[i] - p[now];
			sort(pp, pp + tot);
			for(int i = 0; i < m << 1; ++i)
			{
				ord[i] = i;
				seg[i] = seg[i] - p[now];
			}
			sort(ord, ord + (m << 1), cmp);
			sp.clear();
			memset(vis, 0, sizeof vis);
			Vec[0] = (Point){0, 0};
			Vec[1] = (Point){(int)3e6, -1};
			for(int i = 0; i < m; ++i)
				if(isins(Vec[0], Vec[1], seg[i << 1], seg[i << 1 | 1]))
				{
					vis[i] = 1;
					sp.insert(i);
				}
			for(int i = 0, j = 0; i < tot || j < m << 1; )
			{
				if(j >= m << 1 || i < tot && pp[i] < seg[ord[j]])
				{
					Vec[1] = pp[i];
					set<int>::iterator it = sp.begin();
					if(it == sp.end() || !isins((Point){0, 0}, pp[i], seg[(*it) << 1], seg[(*it) << 1 | 1]))
						++ans;
					++i;
				}
				else
				{
					Vec[1] = seg[ord[j]];
					if(vis[ord[j] >> 1])
					{
						vis[ord[j] >> 1] = 0;
						sp.erase(ord[j] >> 1);
					}
					else
					{
						vis[ord[j] >> 1] = 1;
						sp.insert(ord[j] >> 1);
					}
					++j;
				}
			}
			printf("%d\n", ans);
			for(int i = 0; i < m << 1; ++i)
				seg[i] = seg[i] + p[now];
		}
	}
	return 0;
}
