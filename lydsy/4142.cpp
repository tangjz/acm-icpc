#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 1010;
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
	{
		for(int j = 1; j <= n; ++j)
			ans3[i] = max(ans3[i], (s[i + j - 1] - s[j - 1]).mode2());
		ans2 = max(ans2, ans3[i]);
	}
	printf("%lld\n%lld\n", ans1, ans2);
	for(int i = 1; i <= n; ++i)
		printf("%lld%c", ans3[i], " \n"[i == n]);
	return 0;
}
