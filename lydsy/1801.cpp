#include <stdio.h>
#include <cstring>
typedef long long LL;
const int maxn = 101, mod = 9999973;
int n, m, f[2][maxn][maxn], cur, pre = 1;
int main()
{
	scanf("%d%d", &n, &m);
	f[cur][0][m] = 1;
	for(int i = 1; i <= n; ++i)
	{
		pre ^= 1;
		cur ^= 1;
		// 0
		memcpy(f[cur], f[pre], sizeof f[0]);
		for(int j = 0; j <= m; ++j)
			for(int k = 0; k <= m - j; ++k)
			{
				if(!f[pre][j][k])
					continue;
				// 1
				if(k > 0)
					f[cur][j + 1][k - 1] = (f[cur][j + 1][k - 1] + (LL)k * f[pre][j][k]) % mod;
				if(j > 0)
					f[cur][j - 1][k] = (f[cur][j - 1][k] + (LL)j * f[pre][j][k]) % mod;
				// 2
				if(k > 1)
					f[cur][j + 2][k - 2] = (f[cur][j + 2][k - 2] + ((k * (k - 1LL)) >> 1) * f[pre][j][k]) % mod;
				if(j > 1)
					f[cur][j - 2][k] = (f[cur][j - 2][k] + ((j * (j - 1LL)) >> 1) * f[pre][j][k]) % mod;
				if(k > 0 && j > 0)
					f[cur][j][k - 1] = (f[cur][j][k - 1] + (LL)j * k * f[pre][j][k]) % mod;
			}
	}
	int ans = 0;
	for(int i = 0; i <= m; ++i)
		for(int j = 0; j <= m - i; ++j)
			if((ans += f[cur][i][j]) >= mod)
				ans -= mod;
	printf("%d\n", ans);
	return 0;
}
