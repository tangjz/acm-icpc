#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn = 201, maxm = maxn * maxn;
int t, n, x[maxn], y[maxn], tot, cnt, ans, pos;
pair<int, int> p[maxm];
inline int sqr(int x)
{
	return x * x;
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			scanf("%d", x + i);
		for(int i = 1; i <= n; ++i)
			scanf("%d", y + i);
		tot = cnt = 0;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
			{
				scanf("%d", &p[tot].second);
				if(p[tot].second)
					++cnt;
				p[tot++].first = sqr(x[i] - x[j]) + sqr(y[i] - y[j]);
			}
		sort(p, p + tot);
		ans = tot + 1;
		for(int i = 0, j, c = 0; i < tot; i = j)
		{
			for(j = i; j < tot && p[i].first == p[j].first; ++j)
				if(p[j].second)
					++c;
			if(ans > j + cnt - (c << 1))
			{
				ans = j + cnt - (c << 1);
				pos = p[i].first;
			}
		}
		printf("Case #%d: %d %d\n", Case, pos, ans);
	}
	return 0;
}
