#include <cstdio>
typedef long long LL;
const int maxm = 51;
int n, m, mod, c[maxm][maxm], last, cur, f[2][maxm];
int mod_pow(int x, int k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (LL)ret * x % mod;
		x = (LL)x * x % mod;
		k >>= 1;
	}
	return ret;
}
void query(int n)
{
	if(n == 1)
	{
		for(int i = 0; i <= m; ++i)
			f[cur][i] = m % mod;
		return;
	}
	if(n & 1)
	{
		query(n - 1);
		last ^= 1;
		cur ^= 1;
		for(int i = 0; i <= m; ++i)
		{
			f[cur][i] = 0;
			for(int j = 0; j <= i; ++j)
				f[cur][i] = (f[cur][i] + (LL)c[i][j] * f[last][j]) % mod;
			f[cur][i] = (f[cur][i] + 1LL) * m % mod;
		}
	}
	else
	{
		query(n >> 1);
		last ^= 1;
		cur ^= 1;
		for(int i = 0; i <= m; ++i)
		{
			f[cur][i] = 0;
			for(int j = i, o = 1; j >= 0; --j, o = (LL)o * (n >> 1) % mod)
				f[cur][i] = (f[cur][i] + (LL)c[i][j] * o % mod * f[last][j]) % mod;
			f[cur][i] = ((LL)f[cur][i] * mod_pow(m, n >> 1) + f[last][i]) % mod;
		}
	}
}
int main()
{
	scanf("%d%d%d", &n, &m, &mod);
	for(int i = 0; i <= m; ++i)
	{
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			c[i][j] = ((LL)c[i - 1][j - 1] + c[i - 1][j]) % mod;
	}
	last = 1;
	query(n);
	printf("%d\n", f[cur][m]);
	return 0;
}

