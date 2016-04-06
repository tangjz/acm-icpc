#include <cstdio>
const int maxn = 2001, maxm = 2001, mod = 1000000007;
int n, m, f[maxn][maxm];
char s[maxn];
void inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
int main()
{
	scanf("%d%d%s", &n, &m, s + 1);
	f[0][0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		s[i] -= 'a' - 1;
		for(int j = 0; j <= m; ++j)
		{
			f[i][j] = (long long)f[i - 1][j] * s[i] % mod;
			for(int k = 1; k <= i && k * (n - i + 1) <= j; ++k)
				inc(f[i][j], (long long)(f[i - k][j - k * (n - i + 1)] - (k < i ? f[i - k - 1][j - k * (n - i + 1)] : 0) + mod) * (26 - s[i]) % mod);
		}
	}
	printf("%d\n", f[n][m]);
	return 0;
}
