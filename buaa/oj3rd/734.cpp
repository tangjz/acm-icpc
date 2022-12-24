#include <cmath>
#include <cstdio>
template<class T> T abs(const T& x)
{
	return x < 0 ? -x : x;
}
struct Point
{
	double x, y, z;
	Point operator - (const Point &a) const
	{
		return (Point){x - a.x, y - a.y, z - a.z};
	}
	double dot(const Point &a) const
	{
		return x * a.x + y * a.y + z * a.z;
	}
	Point cross(const Point &a) const
	{
		return (Point){
			y * a.z - z * a.y,
			x * a.z - z * a.x,
			x * a.y - y * a.x
		};
	}
	double norm() const
	{
		return sqrt(x * x + y * y + z * z);
	}
} a, b, m, n;
int t, x, y, z;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d", &x, &y, &z);
		a = (Point){0, y, z};
		b = (Point){x, 0, -z};
		m = (Point){0, y, 0};
		n = a.cross(b);
		printf("%.5f\n", abs(m.dot(n) / n.norm()));
	}
	return 0;
}
