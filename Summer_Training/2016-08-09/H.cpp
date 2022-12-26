#include <cstdio>
typedef long long LL;
const int maxn = 2001, mod = 1000000007;
int t, n, m, c[maxn][maxn];
int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
int main()
{
	for(int i = 0; i < maxn; ++i)
	{
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			if((c[i][j] = c[i - 1][j - 1] + c[i - 1][j]) >= mod - 1)
				c[i][j] -= mod - 1;
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		int ans = 1;
		if(n > 1)
			for(int i = 2; i <= m; ++i)
				ans = (LL)ans * mod_pow(i, (LL)n * c[m - i + n - 2][n - 2] % (mod - 1)) % mod;
		else
			ans = m;
		printf("%d\n", ans);
	}
	return 0;
}
