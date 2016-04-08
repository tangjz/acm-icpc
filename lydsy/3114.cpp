#include <cstdio>
const int mod = 1e9 + 7;
int t, m, a, k, n, now, tmp, ans;
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		n = ans = 1;
		scanf("%d", &m);
		while(m--)
		{
			now = tmp = 1;
			scanf("%d%d", &a, &k);
			for(int i = 1; i <= k; ++i)
			{
				now = (long long)now * a % mod;
				tmp += now;
				if(tmp >= mod)
					tmp -= mod;
			}
			tmp += (long long)now * k % mod;
			if(tmp >= mod)
				tmp -= mod;
			ans = (long long)ans * tmp % mod;
			n = (long long)n * now % mod;
		}
		ans += n;
		if(ans >= mod)
			ans -= mod;
		printf("Case %d: %d\n", Case, ans);
	}
	return 0;
}
