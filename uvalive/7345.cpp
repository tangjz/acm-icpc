#include <cmath>
#include <stdio.h>
#include <cassert>
#include <algorithm>
#include <unordered_set>
typedef long double DB;
const int maxn = 11;
const DB eps = 1e-8, pi = acos(-1.0);
int t, n, m;
DB a, p[maxn], rad, theta, ans;
std::unordered_set<int> cover[maxn];
inline int sgn(DB x)
{
	assert(!std::isnan(x));
	return (x > eps) - (x < -eps);
}
inline int dcmp(DB x, DB y)
{
	return sgn(x - y);
}
bool cmp(DB const& x, DB const& y)
{
	return sgn(x - y) < 0;
}
inline void read(DB &x)
{
	double tp;
	scanf("%lf", &tp);
	x = tp;
}
inline DB sqr(DB x)
{
	return x * x;
}
inline DB cub(DB x)
{
	return x * x * x;
}
inline DB f(int k, DB low, DB upp) // -1 <= k, 0 <= low < upp <= 2 pi
{
	return k >= 0 ? sqr(a) * pi * (sqr(upp) - sqr(low) + 2 * pi * (k << 1 | 1) * (upp - low)) : sqr(a) / 6.0 * (cub(upp) - cub(low));
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		read(a);
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
		{
			read(p[i]);
			std::unordered_set<int>().swap(cover[i]);
		}
		std::sort(p, p + n, cmp);
		scanf("%d", &m);
		if(!n && m)
		{
			while(m--)
			{
				read(rad);
				read(theta);
			}
			printf("Spiral %d: -1\n", Case);
			continue;
		}
		ans = 0;
		while(m--)
		{
			read(rad);
			read(theta);
			int k = (int)((rad - a * theta) / (2 * pi * a)); // inside
			for( ; dcmp(rad, a * (theta + 2 * pi * k)) < 0; --k);
			for( ; dcmp(rad, a * (theta + 2 * pi * (k + 1))) > 0; ++k);
			int idx = std::upper_bound(p, p + n, theta, cmp) - p; // p[idx - 1] -> p[idx]
			if(idx == n)
			{
				idx = 0;
				++k;
			}
			if(cover[idx].count(k))
				continue;
			cover[idx].insert(k);
			ans += idx ? f(k, p[idx - 1], p[idx]) : f(k, 0.0, p[0]) + (k >= 0 ? f(k - 1, p[n - 1], 2 * pi) : 0);
		}
		printf("Spiral %d: %.4f liters\n", Case, (double)(ans / 10.0));
	}
	return 0;
}
