#include <cstdio>
#include <algorithm>
const int maxn = 510;
int t, n, h, w, a[maxn], ans;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d", &n, &h, &w);
		a[0] = 0;
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		a[n + 1] = w;
		std::sort(a + 1, a + n + 1);
		ans = w;
		for(int i = 0; i <= n; ++i)
			ans = std::min(ans, a[i + 1] - a[i]);
		ans *= h;
		printf("%d\n", ans);
	}
	return 0;
}
