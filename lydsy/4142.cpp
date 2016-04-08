#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 1010, maxt = 4000;
const double eps = 1e-8, pi = acos(-1);
int n;
LL ans1, ans2, ans3[maxn];
struct Point
{
	int x, y;
	Point operator + (const Point &t) const
	{
		return (Point){x + t.x, y + t.y};
	}
	Point operator - (const Point &t) const
	{
		return (Point){x - t.x, y - t.y};
	}
	LL det(const Point &t) const
	{
		return (LL)x * t.y - (LL)y * t.x;
	}
	LL dot(const Point &t) const
	{
		return (LL)x * t.x + (LL)y * t.y;
	}
	LL mode2() const
	{
		return dot(*this);
	}
	bool operator < (const Point &t) const
	{
		if(y == 0 && t.y == 0 && x * t.x <= 0)
			return x > t.x;
		if(y == 0 && x >= 0 && t.y != 0)
			return 1;
		if(t.y == 0 && t.x >= 0 && y != 0)
			return 0;
		if(t.y * y <= 0)
			return y > t.y;
		LL ret = det(t);
		return ret > 0 || (ret == 0 && x < t.x);
	}
} pp, p[maxn], s[maxn << 1];
double theta, xx, yy;
int dcmp(double x)
{
	return (x > eps) - (x < -eps);
}
bool cmp(const Point &a, const Point &b)
{
	return dcmp((a.x - b.x) * xx + (a.y - b.y) * yy) > 0;
}
int main()
{
	scanf("%d%d%d", &n, &pp.x, &pp.y);
	for(int i = 1; i <= n; ++i)
		scanf("%d%d", &p[i].x, &p[i].y);
	sort(p + 1, p + n + 1);
	for(int i = 1; i <= n; ++i)
	{
		ans1 += max(pp.dot(p[i]), 0LL);
		s[i] = s[i - 1] + p[i];
	}
	for(int i = 1; i <= n; ++i)
		s[n + i] = s[n + i - 1] + p[i];
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			ans2 = max(ans2, (s[i + j - 1] - s[j - 1]).mode2());
	for(int t = 0; t < maxt; ++t)
	{
		theta = 2.0 * t / maxt * pi;
		xx = maxt * cos(theta);
		yy = maxt * sin(theta);
		sort(p + 1, p + n + 1, cmp);
		Point sum = (Point){0, 0};
		for(int i = 1; i <= n; ++i)
		{
			sum = sum + p[i];
			ans3[i] = max(ans3[i], sum.mode2());
		}
	}
	printf("%lld\n%lld\n", ans1, ans2);
	for(int i = 1; i <= n; ++i)
		printf("%lld%c", ans3[i], " \n"[i == n]);	
	return 0;
}
