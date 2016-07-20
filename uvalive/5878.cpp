#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 233;

struct Point
{
	int x, y;
	int dot(const Point &t) const
	{
		return x * t.x + y * t.y;
	}
	int det(const Point &t) const
	{
		return x * t.y - y * t.x;
	}
	double mode() const
	{
		return sqrt(dot(*this));
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
		int ret = det(t);
		return ret > 0 || (ret == 0 && x < t.x);	
	}
	Point operator + (const Point &t) const
	{
		return (Point){x + t.x, y + t.y};
	}
	Point operator - (const Point &t) const
	{
		return (Point){x - t.x, y - t.y};
	}
} p[maxn], s[maxn], ans;
int n;
int main()
{
	while(scanf("%d", &n) == 1 && n)
	{
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d%d", &p[i].x, &p[i].y);
			p[n + i].x = -p[i].x;
			p[n + i].y = -p[i].y;
		}
		sort(p + 1, p + n * 2 + 1);
		//printf("sorted:\n");
		//for(int i = 1; i <= n * 2; ++i)
		//	printf("%d %d\n", p[i].x, p[i].y);
		for(int i = 1; i <= n * 2; ++i)
			s[i] = s[i - 1] + p[i];
		ans = (Point){0, 0};
		for(int i = 1; i <= n * 2; ++i)
			for(int j = 1; j <= n && j <= i; ++j)
				if(ans.dot(ans) < (s[i] - s[i - j]).dot(s[i] - s[i - j]))
					ans = s[i] - s[i - j];
		printf("%.3f\n", ans.mode());
	}
	return 0;
}
