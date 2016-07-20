#include <cstdio>
typedef long long LL;
const int maxn = 501, mod = 1000000007;
int c[maxn][maxn], fact[maxn], t, n, m, p, ans;
int main()
{
	fact[0] = c[0][0] = 1;
	for(int i = 1; i < maxn; ++i)
	{
		fact[i] = (LL)fact[i - 1] * i % mod;
		c[i][0] = 1;
		for(int j = 1; j < i; ++j)
			if((c[i][j] = c[i - 1][j - 1] + c[i - 1][j]) >= mod)
				c[i][j] -= mod;
		c[i][i] = 1;
	}
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d%d", &n, &m, &p);
		ans = 0;
		for(int i = 1; i <= n - m; ++i)
			for(int j = 1; j <= n - p && j <= i; ++j)
				ans = (ans + (LL)c[n - p][j] * c[p - 1][i - j] % mod * fact[n - 1 - i]) % mod;
		if(n - p <= m - 1)
			ans = (ans + (LL)c[m - 1][n - p] * fact[n - p] % mod * c[p - 1][n - m] % mod * fact[m - 1 - (n - p)]) % mod;
		printf("Case #%d: %d\n", Case, ans);
	}
}
