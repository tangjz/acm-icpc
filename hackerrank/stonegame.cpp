#include <stdio.h>
typedef long long LL;
const int maxn = 101, mod = 1000000007;
int n, a[maxn], f[3], ans;
int solve()
{
	int ret = 1;
	for(int i = 29; i >= 0; --i)
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
		if((ret += f[1 + (o ^ 1)]) >= mod)
			ret -= mod;
		if(o)
		{
			if(--ret < 0)
				ret += mod;
			break;
		}
	}
	return ret;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	ans = solve();
	for(int i = 0; i < n; ++i)
		--a[i];
	if((ans -= solve()) < 0)
		ans += mod;
	printf("%d\n", ans);
	return 0;
}
