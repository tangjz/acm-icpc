#include <stdio.h>
typedef long long LL;
const int maxn = 100001, maxd = 30, mod = 1000000007;
int pw[maxn], t, n, a[maxn], ans;
int main()
{
	pw[0] = 1;
	for(int i = 1; i < maxn; ++i)
		if((pw[i] = pw[i - 1] << 1) >= mod)
			pw[i] -= mod;
	scanf("%d", &t);
	while(t--)
	{
		ans = 0;
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		for(int i = 0; i < maxd; ++i)
		{
			int cnt = 0;
			for(int j = 0; j < n; ++j)
				if(a[j] & (1 << i))
					++cnt;
			if(!cnt)
				continue;
			int val = (1LL << i) * pw[n - 1] % mod;
			if((ans += val) >= mod)
				ans -= mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
