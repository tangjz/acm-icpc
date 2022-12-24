#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100001, mod = 1000000007;
int pw[maxn], n, l[maxn], r[maxn], tot, que[maxn << 1], cnt[maxn << 1], ans;
int main()
{
	pw[0] = 1;
	for(int i = 1; i < maxn; ++i)
	{
		pw[i] = pw[i - 1] << 1;
		if(pw[i] >= mod)
			pw[i] -= mod;
	}
	while(scanf("%d", &n) == 1)
	{
		tot = ans = 0;
		memset(cnt, 0, sizeof cnt);
		for(int i = 0; i < n; ++i)
		{
			scanf("%d%d", l + i, r + i);
			que[tot++] = l[i];
			que[tot++] = r[i];
		}
		sort(que, que + tot);
		tot = unique(que, que + tot) - que;
		for(int i = 0; i < n; ++i)
		{
			l[i] = lower_bound(que, que + tot, l[i]) - que + 1;
			r[i] = lower_bound(que, que + tot, r[i]) - que + 1;
			++cnt[l[i]];
			--cnt[r[i]];
		}
		for(int i = 1; i < tot; ++i)
		{
			cnt[i] += cnt[i - 1];
			ans = (ans + (LL)(que[i] - que[i - 1]) * (pw[n] - pw[n - cnt[i]])) % mod;
		}
		if(ans < 0)
			ans += mod;
		printf("%d\n", ans);
	}
	return 0;
}
