#include <stdio.h>
#include <algorithm>
const int maxn = 100003;
int n, a[maxn], f[maxn], tot, que[maxn], cnt[2][maxn];
long long ans;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	a[0] = f[n + 1] = f[n + 2] = 0;
	que[tot++] = 0;
	for(int i = n; i >= 1; --i)
	{
		f[i] = f[i + 2] ^ (a[i] - a[i - 1]);
		que[tot++] = f[i];
	}
	std::sort(que, que + tot);
	tot = std::unique(que, que + tot) - que;
	que[tot] = ~0u >> 1;
	for(int i = n; i >= 1; --i)
	{
		ans += cnt[~i & 1][std::lower_bound(que, que + tot, f[i + 1]) - que];
		int val = a[i] ^ f[i + 2], idx = std::lower_bound(que, que + tot, val) - que;
		if(que[idx] == val)
			ans += cnt[i & 1][idx];
		++cnt[i & 1][std::lower_bound(que, que + tot, f[i + 2]) - que];
	}
	printf("%lld\n", (n * (n - 1LL) >> 1) - ans);
	return 0;
}
