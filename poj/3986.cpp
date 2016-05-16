#include <stdio.h>
typedef long long LL;
const int maxn = 51, mod = 1000000003;
int n, k, a[maxn], f[3], ans;
int main()
{
	while(scanf("%d%d", &n, &k) == 2 && !(!n && !k))
	{
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		int ans = 1;
		for(int i = 30; i >= 0; --i)
		{
			int o = 0, all = (1u << i) - 1;
			f[0] = 1;
			f[1] = f[2] = 0;
			for(int j = 0; j < n; ++j)
			{
				int val = (a[j] & all) + 1;
				if((a[j] >> i) & 1)
				{
					long long tmp[2] = {f[0] + ((LL)f[2] << i), (LL)f[1] << i};
					o ^= 1;
					f[0] = (LL)f[0] * val % mod;
					f[1] = ((LL)f[1] * val + tmp[0]) % mod;
					f[2] = ((LL)f[2] * val + tmp[1]) % mod;
				}
				else
				{
					f[0] = (LL)f[0] * val % mod;
					f[1] = (LL)f[1] * val % mod;
					f[2] = (LL)f[2] * val % mod;
				}
			}
			if((ans += f[1 + (o ^ ((k >> i) & 1) ^ 1)]) >= mod)
				ans -= mod;
			if(o ^ ((k >> i) & 1))
			{
				if(--ans < 0)
					ans += mod;
				break;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

