#include <stdio.h>
typedef long long LL;
const int maxn = 201, mod = 100000007;
int n, f[2][maxn][maxn], cur, pre = 1, ans;
int main()
{
	scanf("%d", &n);
	f[cur][0][0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		cur ^= 1;
		pre ^= 1;
		for(int j = 0; j <= i; ++j)
			for(int k = 0; k <= i - j; ++k)
				f[cur][j][k] = 0;
		for(int j = 0; j < i; ++j)
			for(int k = 0; k < i - j; ++k)
			{
				if(!f[pre][j][k])
					continue;
				// add 0
				if((f[cur][j + 1][k] += f[pre][j][k]) >= mod)
					f[cur][j + 1][k] -= mod;
				// add 1
				f[cur][j][k + 1] = (f[cur][j][k + 1] + (LL)(j + 1) * f[pre][j][k]) % mod;
				if(k > 0)
					f[cur][j + 1][k - 1] = (f[cur][j + 1][k - 1] + (LL)k * f[pre][j][k]) % mod;
				// add 1+1
				if(j > 0)
					f[cur][j - 1][k + 2] = (f[cur][j - 1][k + 2] + (LL)((j * (j + 1)) >> 1) * f[pre][j][k]) % mod;
				if(k > 1)
					f[cur][j + 1][k - 2] = (f[cur][j + 1][k - 2] + (LL)((k * (k - 1)) >> 1) * f[pre][j][k]) % mod;
				if(k > 0)
					f[cur][j][k] = (f[cur][j][k] + (LL)((j + 1) * k) * f[pre][j][k]) % mod;
				// add 2
				f[cur][j][k] = (f[cur][j][k] + (LL)(j + 1) * f[pre][j][k]) % mod;
			}
	}
	for(int i = 0; i <= n; ++i)
		for(int j = 0; j <= n - i; ++j)
			if((ans += f[cur][i][j]) >= mod)
				ans -= mod;
	printf("%d\n", ans);
	return 0;
}
