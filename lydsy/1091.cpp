#include <cmath>
#include <stdio.h>
#include <cassert>
#include <algorithm>
const int maxn = 9;
const double eps = 1e-8, INF = 1e10;
inline int sgn(double x)
{
	assert(!std::isnan(x));
	return (x > eps) - (x < -eps);
}
inline int dcmp(double x, double y)
{
	return sgn(x - y);
}
struct Point {
	double x, y;
	Point operator - (Point const& t) const {
		return (Point){x - t.x, y - t.y};
	}
	double det(Point const& t) const {
		return x * t.y - y * t.x;
	}
	double norm() const {
		return sqrt(x * x + y * y);
	}
} p[maxn];
struct Line {
	Point s, t;
} a[maxn], b[maxn + 4];
int n, tot, perm[maxn];
double R, C;
int main()
{
	scanf("%lf%lf%d", &R, &C, &n);
	for(int i = 0; i < 4; ++i)
	{
		p[i].x = (i & 1) == (i >> 1) ? 0 : R;
		p[i].y = i >> 1 ? C : 0;
	}
	for(int i = 0; i < 4; ++i)
		b[i] = (Line){p[i], p[i + 1 < 4 ? i + 1 : 0] - p[i]};
	for(int i = 0; i < n; ++i)
	{
		scanf("%lf%lf", &p[i].x, &p[i].y);
		perm[i] = i;
	}
	for(int i = 0; i < n; ++i)
		a[i] = (Line){p[i], p[i + 1 < n ? i + 1 : 0] - p[i]};
	double ans = INF;
	do
	{
		double cost = 0;
		tot = 4;
		for(int i = 0; i < n; ++i)
		{
			Line &cur = a[perm[i]];
			double low = -INF, upp = INF;
			for(int j = 0; j < tot; ++j)
			{
				double dt = b[j].t.det(b[j].s - cur.s) / b[j].t.det(cur.t);
				if(dcmp(dt, 0.5) > 0)
				{
					if(dt < upp)
						upp = dt;
				}
				else
				{
					if(low < dt)
						low = dt;
				}
			}
			b[tot++] = cur;
			cost += (upp - low) * cur.t.norm();
		}
		if(cost < ans)
			ans = cost;
	} while(std::next_permutation(perm, perm + n));
	printf("%.3f\n", ans);
	return 0;
}
