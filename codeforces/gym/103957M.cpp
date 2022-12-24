#include <cstdio>
#include <algorithm>
const int maxn = 1001;
int t, n, m, tot, ans1, ans2;
std::pair<int, int> a[maxn];
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		ans1 = ans2 = 0;
		scanf("%d%d%d", &n, &m, &tot);
		for(int i = 0; i < tot; ++i)
			scanf("%d%d", &a[i].first, &a[i].second);
		std::sort(a, a + tot);
		tot = std::unique(a, a + tot) - a;
		for(int i = 0, j = 0; i < n; ++i)
		{
			int cur = -1, len;
			for( ; j < tot && a[j].first == i; cur = a[j++].second)
			{
				len = a[j].second - cur - 1;
				ans1 += (len + 1) >> 1;
				ans2 += (len + 2) / 3;
			}
			len = m - cur - 1;
			ans1 += (len + 1) >> 1;
			ans2 += (len + 2) / 3;
		}
		printf("Case #%d: %d %d\n", Case, ans1, ans2);
	}
	return 0;
}
