#include <stdio.h>
#include <algorithm>
using namespace std;
#define x first
#define y second
typedef pair<double, double> Point;
const int maxn = 100001;
const double eps = 1e-8;
int t, n, sz, stk[maxn];
Point O, p[maxn];
int sgn(double x)
{
	return (x > eps) - (x < -eps);
}
double area(Point S, Point A, Point B)
{
	return (A.x - S.x) * (B.y - S.y) - (A.y - S.y) * (B.x - S.x);
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 0, w, s = 0; i < n; ++i)
		{
			scanf("%d", &w);
			s += w;
			p[i] = make_pair(s, s / (double)w);
		}
		sort(p, p + n);
		sz = 0;
		for(int i = 0; i < n; ++i)
		{
			for( ; sz > 1 && sgn(area(p[stk[sz - 2]], p[stk[sz - 1]], p[i])) <= 0; --sz);
			stk[sz++] = i;
		}
		for(int i = n - 2, tp = sz; i >= 0; --i)
		{
			for( ; sz > tp && sgn(area(p[stk[sz - 2]], p[stk[sz - 1]], p[i])) <= 0; --sz);
			stk[sz++] = i;
		}
		if(n > 1)
			--sz;
		double ans = area(O, p[stk[sz - 1]], p[stk[0]]);
		for(int i = 1; i < sz; ++i)
			ans += area(O, p[stk[i - 1]], p[stk[i]]);
		printf("%.5f\n", 0.5 * ans);
	}
	return 0;
}
