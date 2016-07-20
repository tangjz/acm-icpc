#include <cmath>
#include <cstdio>
const double eps = 1e-8, pi = acos(-1.0);
int sgn(double x)
{
	return (x > eps) - (x < -eps);
}
struct Point
{
	double x, y;
	Point operator - (const Point &t) const
	{
		return (Point){x - t.x, y - t.y};
	}
	Point operator + (const Point &t) const
	{
		return (Point){x + t.x, y + t.y};
	}
	Point operator * (const double &t) const
	{
		return (Point){x * t, y * t};
	}
	Point operator / (const double &t) const
	{
		return (Point){x / t, y / t};
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
	Point unit() const
	{
		double len = mode();
		return sgn(len) ? *this / len : *this;
	}
	Point trans() const
	{
		return (Point){y, -x};
	}
} p[10];
Point PointOfLineReflection(Point P, Point A, Point B)
{
	Point dir = (B - A).unit();
	return P + dir.trans() * (dir.det(P - A) * 2);
}
double DistanceOfPointToSegment(Point P, Point A, Point B)
{
	Point dir = (B - A).unit(), Q = P + dir.trans() * dir.det(P - A);
	bool flag1 = sgn((B - A).dot(Q - A)) >= 0, flag2 = sgn((A - B).dot(Q - B)) >= 0;
	return flag1 && flag2 ? fabs((B - A).unit().det(P - A)) : (flag1 ? (Q - B).mode() : (Q - A).mode());
}
double w, l, r, h, d, theta;
int main()
{
	while(scanf("%lf%lf%lf", &w, &l, &r) == 3)
	{
		for(int i = 1; i <= 3; ++i)
			scanf("%lf%lf", &p[i].x, &p[i].y);
		scanf("%lf", &h);
		p[4] = (Point){0, l};
		p[5] = (Point){w, l};
		p[6] = p[2] + (p[2] - p[4]).unit() * (r * 2);
		p[7] = p[3] + (p[3] - p[5]).unit() * (r * 2);
		p[8] = p[1] + (p[1] - p[7]).unit() * (r * 2);
		p[9] = PointOfLineReflection(p[6], p[1], p[7]);
		if(sgn((p[8] - p[9]).dot(p[7] - p[1])) <= 0
		|| sgn((p[6] - p[8]).dot(p[4] - p[2])) <= 0
		|| sgn((p[7] - p[1]).dot(p[5] - p[3])) <= 0)
		{
			puts("impossible");
			continue;
		}
		d = (h - p[9].y) / (p[8].y - p[9].y) * (p[8].x - p[9].x) + p[9].x;
		theta = atan2(p[8].y - p[9].y, p[8].x - p[9].x);
		p[0] = (Point){d, h};
		if(sgn(theta) <= 0 || sgn(d - r) < 0 || sgn(d + r - w) > 0
		|| sgn(DistanceOfPointToSegment(p[2], p[0], p[8]) - r * 2) < 0)
		{
			puts("impossible");
			continue;
		}
		printf("%.2f %.2f\n", d, theta / pi * 180.0);
	}
	return 0;
}
