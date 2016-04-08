#include <cstdio>
typedef long long LL;
const int maxn = 1001, mod = 1000000007;
int n, f[2][maxn * 9], p, ans;
int main()
{
	scanf("%d", &n);
	f[0][0] = 1;
	for(int i = 1; i <= n; ++i, p ^= 1)
		for(int j = 0; j <= 9 * i; ++j)
		{
			f[!p][j] = 0;
			for(int k = 0; k <= 9 && k <= j; ++k)
			{
				f[!p][j] += f[p][j - k];
				if(f[!p][j] >= mod)
					f[!p][j] -= mod;
			}
		}
	for(int i = 0; i <= 9 * n; ++i)
		ans = (ans + (LL)f[p][i] * (f[p][i] - f[!p][i])) % mod;
	if(ans < 0)
		ans += mod;
	printf("%d\n", ans);
	return 0;
}
