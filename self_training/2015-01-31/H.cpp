#include <cmath>
#include <cstdio>
int t, n;
double ans;
struct Point
{
	double x, y;
	Point operator - (const Point &t) const
	{
		return (Point){x - t.x, y - t.y};
	}
	double operator * (const Point &t) const
	{
		return x * t.y - y * t.x;
	}
} a[10], b;
struct Line
{
	Point p1, p2;
};
double norm(Point a)
{
	return sqrt(a.x * a.x + a.y * a.y);
}
double dis(Point a, Line b)
{
	double tmp = fabs((a - b.p1) * (b.p2 - b.p1)) / norm(b.p2 - b.p1);
	double tmp1 = sqrt((b.p1.x - a.x) * (b.p1.x - a.x) + (b.p1.y - a.y) * (b.p1.y - a.y) - tmp * tmp);
	double tmp2 = sqrt((b.p2.x - a.x) * (b.p2.x - a.x) + (b.p2.y - a.y) * (b.p2.y - a.y) - tmp * tmp);
	if(fabs(tmp1 + tmp2 - norm(b.p2 - b.p1)) <= 1e-8)
		return tmp;
	else
		return 1e60;
}
double min(double x, double y)
{
	return x < y ? x : y;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%lf%lf", &a[i].x, &a[i].y);
		scanf("%lf%lf", &b.x, &b.y);
		ans = 1e60;
		for(int i = 1; i < n; ++i)
			ans = min(ans, dis(b, (Line){a[i - 1], a[i]}));
		if(n > 1)
			ans = min(ans, dis(b, (Line){a[0], a[n - 1]}));
		else
			ans = 0;
		printf("%.3f\n", ans);
	}
	return 0;
}
