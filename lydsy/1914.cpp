/*
 * 容斥算反面，按极角序排序，维护一个不合法区段，即两条夹角小于180度的射线中间又夹了一条射线的数量 
 */
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
int n;
LL ans;
struct Point
{
	int x, y, a;
	Point(int x = 0, int y = 0, int a = 0) : x(x), y(y), a(a) {}
	bool operator < (const Point &t) const { return a < t.a || a == t.a && (LL)y * t.x < (LL)x * t.y; }
	LL det(const Point &t) { return (LL)x * t.y - (LL)y * t.x; }
}p[200010];
int main()
{
	scanf("%d", &n);
	if(n < 3) { puts("0"); return 0; }
	for(int i = 0; i < n; i ++)
	{
		int x, y, area;
		scanf("%d%d", &x, &y);
		if(x >= 0 && y >= 0) area = 2;
		else if(x <= 0 && y <= 0) area = 0;
		else if(x > 0 && y < 0) area = 1;
		else area = 3;
		p[i] = Point(x, y, area);
	}
	sort(p, p + n);
	for(int i = 0; i < n; ++i) p[i + n] = p[i];
	for(int i = 0, j = 0; i < n; ++i)
	{
		while(j < i + n && p[i].det(p[j]) >= 0) ++j;
		if(j - i >= 3) ans += (LL)(j - i - 2) * (j - i - 1) >> 1;
	}
	printf("%lld\n", (LL)n * (n - 1) * (n - 2) / 6 - ans);
	return 0;
}
