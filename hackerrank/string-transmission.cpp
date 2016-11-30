#include <stdio.h>
#include <cstring>
typedef long long LL;
const int maxn = 1001, mod = 1000000007;
int fact[maxn], iact[maxn];
int t, n, m, a[maxn], c[maxn], f[2][maxn], cur, nxt = 1, g[maxn], ans;
char str[maxn];
inline int C(int n, int m)
{
	return (LL)fact[n] * iact[m] % mod * iact[n - m] % mod;
}
int main()
{
	iact[1] = 1;
	for(int i = 2; i < maxn; ++i)
		iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
	fact[0] = iact[0] = 1;
	for(int i = 1; i < maxn; ++i)
	{
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%s", &n, &m, str);
		ans = 0;
		for(int i = 0; i <= m; ++i)
			if((ans += C(n, i)) >= mod)
				ans -= mod;
		memset(g + 1, 0, n * sizeof(int));
		for(int len = 1; len < n; ++len)
		{
			if(n % len)
				continue;
			int sz = n / len;
			memset(c, 0, len * sizeof(int));
			for(int i = 0; i < n; ++i)
				if(str[i] == '1')
					++c[i % len];
			memset(f[cur], 0, (m + 1) * sizeof(int));
			f[cur][0] = 1;
			for(int i = 0; i < len; ++i)
			{
				for(int j = 0; j <= m; ++j)
				{
					f[nxt][j] = 0;
					if(j >= c[i] && (f[nxt][j] += f[cur][j - c[i]]) >= mod)
						f[nxt][j] -= mod;
					if(j >= sz - c[i] && (f[nxt][j] += f[cur][j - sz + c[i]]) >= mod)
						f[nxt][j] -= mod;
				}
				cur ^= 1;
				nxt ^= 1;
			}
			for(int i = 0; i <= m; ++i)
				if((g[len] += f[cur][i]) >= mod)
					g[len] -= mod;
			for(int i = len << 1; i <= n; i += len)
				if((g[i] -= g[len]) < 0)
					g[i] += mod;
			if((ans -= g[len]) < 0)
				ans += mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
