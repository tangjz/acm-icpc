#include <cstdio>
const int maxn = 3001, mod = 1000000007;
int n, pow2[maxn * maxn], c[maxn][maxn], f[maxn];
int main()
{
	scanf("%d", &n);
	c[0][0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
		{
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
			if(c[i][j] >= mod)
				c[i][j] -= mod;
		}
	}
	pow2[0] = 1;
	for(int i = 1; i <= n * n; ++i)
	{
		pow2[i] = pow2[i - 1] << 1;
		if(pow2[i] >= mod)
			pow2[i] -= mod;
	}
	f[0] = 1;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= i; ++j)
		{
			int tmp = (long long)c[i][j] * pow2[j * (i - j)] % mod * f[i - j] % mod;
			if(!(j & 1) && tmp)
				tmp = mod - tmp;
			f[i] += tmp;
			if(f[i] >= mod)
				f[i] -= mod;
		}
	printf("%d\n", f[n]);
	return 0;
}
