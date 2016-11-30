#include <cmath>
#include <cstdio>
const double eps = 1e-8;
struct Point
{
	double x, y;
	Point operator * (const double &t) const
	{
		return (Point){x * t, y * t};
	}
	Point operator + (const Point &t) const
	{
		return (Point){x + t.x, y + t.y};
	}
	Point operator - (const Point &t) const
	{
		return (Point){x - t.x, y - t.y};
	}
	double norm()
	{
		return sqrt(x * x + y * y);
	}
} A, B, C, D;
int h, d, m;
double calc(double l)
{
	A.x = l / 2 + sqrt(m * m - h * h), A.y = h;
	B.x = 0, B.y = 0;
	C.x = l, C.y = 0;
	double b = (A - C).norm(), c = (A - B).norm();
	D = B + (C - B) * (c / (b + c));
	return (A - D).norm();
}
int main()
{
	scanf("%d%d%d", &h, &d, &m);
	if(h == d && d == m)
	{
		puts("YES");
		printf("%.8f %.8f\n", 0.0, (double)h);
		printf("%.8f %.8f\n", (double)-h, 0.0);
		printf("%.8f %.8f\n", (double)h, 0.0);
	}
	else if(h < d && d < m)
	{
		double L = 0, R = 1e3, M, res;
		while(R - L >= eps)
		{
			res = calc((M = (L + R) / 2));
			if(fabs(res - d) < eps)
				break;
			if(res > d)
				L = M;
			else
				R = M;
		}
		calc((L + R) / 2);
		puts("YES");
		printf("%.8f %.8f\n", A.x, A.y);
		printf("%.8f %.8f\n", B.x, B.y);
		printf("%.8f %.8f\n", C.x, C.y);
	}
	else
		puts("NO");
	return 0;
}
