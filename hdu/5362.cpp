#include <cstdio>
const int maxn = 2010, mod = 1000000007;
typedef long long LL;
int t, n, m, p[maxn], f[maxn][maxn], ans;
void inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		p[0] = 1;
		for(int i = 1; i <= n; ++i)
			p[i] = (LL)p[i - 1] * m % mod;
		ans = 0;
		f[0][0] = 1;
		for(int i = 1; i <= n; ++i)
		{
			for(int j = 0; j <= i; ++j)
			{
				f[i][j] = 0;
				if(i - 1 >= j + 1)
					inc(f[i][j], (LL)f[i - 1][j + 1] * (j + 1) % mod);
				if(j > 0)
					inc(f[i][j], (LL)f[i - 1][j - 1] * (m - j + 1) % mod);
			}
			inc(ans, (LL)(n - i + 1) * p[n - i] % mod * (f[i][0] + f[i][1]) % mod);
		}
		printf("%d\n", ans);
	}
	return 0;
}
