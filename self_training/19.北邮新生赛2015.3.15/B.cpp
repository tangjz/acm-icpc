#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100001;
const double eps = 1e-8;
inline int sgn(double x)
{
	return (x > eps) - (x < -eps);
}
struct Point
{
	int id;
	double x, y;
	bool operator == (const Point &t) const
	{
		return !sgn(x - t.x) && !sgn(y - t.y);
	}
	bool operator < (const Point &t) const
	{
		return sgn(x - t.x) < 0 || !sgn(x - t.x) && sgn(y - t.y) < 0;
	}
	Point operator - (const Point &t) const
	{
		return (Point){id, x - t.x, y - t.y};
	}
	Point operator + (const Point &t) const
	{
		return (Point){id, x + t.x, y + t.y};
	}
	Point operator * (const double &t) const
	{
		return (Point){id, x * t, y * t};
	}
	double dot(const Point &t) const
	{
		return x * t.x + y * t.y;
	}
	double det(const Point &t) const
	{
		return x * t.y - y * t.x;
	}
	double mode() const
	{
		return sqrt(dot(*this));
	}	
} p[maxn], A, B, pp[maxn];
int n, tot;
double ans;
inline bool isIns(Point aL, Point aR, Point bL, Point bR) // Line aL aR  Segment bL bR
{
	return sgn((aR - aL).det(bR - aL)) * sgn((aR - aL).det(bL - aL)) <= 0;
}
inline Point SegIns(Point aL, Point aR, Point bL, Point bR)
{
	Point u = aL - bL, v = aR - aL, w = bR - bL;
	return aL + (aR - aL) * ((bR - bL).det(aL - bL) / (aR - aL).det(bR - bL));
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		for(int i = 0; i < n; ++i)
			scanf("%lf%lf", &p[i].x, &p[i].y);
		scanf("%lf%lf%lf%lf", &A.x, &A.y, &B.x, &B.y);
		tot = 0;
		for(int i = 0; i < n; ++i)
			if(isIns(A, B, p[i], p[(i + 1) % n]))
			{
				pp[tot] = SegIns(A, B, p[i], p[(i + 1) % n]);
				pp[tot++].id = i;
			}
		sort(pp, pp + tot);
		ans = 0;
		for(int i = 0, flag = 0; i < tot; ++i)
		{
			if(flag)
				ans += (pp[i - 1] - pp[i]).mode();
			if(i + 1 < n && pp[i] == pp[i + 1])
			{
				Point a = pp[i] == p[pp[i].id] ? p[(pp[i].id + 1) % n] : p[pp[i].id];
				Point b = pp[i + 1] == p[pp[i + 1].id] ? p[(pp[i + 1].id + 1) % n] : p[pp[i + 1].id];
				if(isIns(A, B, a, b))
					flag ^= 1;
				++i;
			}
			else
				flag ^= 1;
		}
		printf("%.4f\n", ans);
	}
	return 0;
}
