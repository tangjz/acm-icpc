#include <cstdio>
typedef long long LL;
const int maxn = 5001;
int n, mod, c[2][maxn], cur, pre = 1, f[maxn], g[maxn], pw[maxn], ans;
int main()
{
	scanf("%d%d", &n, &mod);
	c[cur][0] = f[0] = pw[0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		cur ^= 1;
		pre ^= 1;
		c[cur][0] = c[cur][i] = 1;
		for(int j = 1; j < i; ++j)
			if((c[cur][j] = c[pre][j - 1] + c[pre][j] - mod) < 0)
				c[cur][j] += mod;
		f[i] = i & 1 ? 0 : (LL)c[cur][i >> 1] * c[cur][i >> 1] % mod;
		pw[i] = 4LL * pw[i - 1] % mod;
	}
	ans = (n + 1LL) * pw[n] % mod;
	for(int i = 2; i <= n; i += 2)
	{
		g[i] = f[i];
		for(int j = 2; j < i; j += 2)
			g[i] = (g[i] - (LL)g[j] * f[i - j]) % mod;
		ans = (ans - (n - i + 1LL) * pw[n - i] % mod * g[i]) % mod;
	}
	if(ans < 0)
		ans += mod;
	printf("%d\n", ans);
	return 0;
}
