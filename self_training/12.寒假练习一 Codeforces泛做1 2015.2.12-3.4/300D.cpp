#include <cstdio>
const int maxm = 29, maxk = 1001, mod = 7340033;
int q, n, k, m;
long long f[maxm][maxk], g[maxk];
int main()
{
	for(int i = 0; i < maxm - 1; ++i)
	{
		f[i][0] = 1;
		for(int j = 0; j < maxk; ++j)
			for(int k = 0; k < maxk - j; ++k)
				g[j + k] += f[i][j] * f[i][k];
		for(int j = 0; j < maxk; ++j)
			g[j] %= mod;
		for(int j = 0; j < maxk; ++j)
			for(int k = 0; k < maxk - j - 1; ++k)
				f[i + 1][j + k + 1] += g[j] * g[k];
		for(int j = 0; j < maxk; ++j)
		{
			f[i + 1][j] %= mod;
			g[j] = 0;
		}
	}
	f[maxm - 1][0] = 1;
	scanf("%d", &q);
	while(q--)
	{
		scanf("%d%d", &n, &k);
		for(m = 0; n > 1 && (n & 1); n >>= 1, ++m);
		printf("%d\n", (int)f[m][k]);
	}
	return 0;
}
