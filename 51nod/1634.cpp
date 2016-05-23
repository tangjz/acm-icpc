#include <cstdio>
typedef long long LL;
const int maxn = 11, mod = 1000000007;
int n, m, pw[maxn * maxn], c[maxn][maxn], f[maxn][maxn];
int main()
{
	for(int i = 0; i < maxn; ++i)
	{
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			if((c[i][j] = c[i - 1][j - 1] + c[i - 1][j]) >= mod)
				c[i][j] -= mod;
	}
	pw[0] = 1;
	for(int i = 1; i < maxn * maxn; ++i)
		pw[i] = 3LL * pw[i - 1] % mod;
	for(int i = 1; i < maxn; ++i)
		for(int j = 0; j < maxn; ++j)
		{
			f[i][j] = pw[i * j];
			for(int a = 1; a <= i; ++a)
				for(int b = 0; b <= j; ++b)
					if(a < i || b < j)
						f[i][j] = (f[i][j] - (LL)c[i - 1][a - 1] * c[j][b] % mod * pw[(i - a) * (j - b)] % mod * f[a][b]) % mod;
			if(f[i][j] < 0)
				f[i][j] += mod;
		}
	while(scanf("%d%d", &n, &m) == 2)
		printf("%d\n", f[n][m]);
	return 0;
}
