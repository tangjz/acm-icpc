#include <cstdio>
typedef long long LL;
const int maxl = 5001;
int n, m, p, fact[maxl], a[maxl], str[maxl][maxl], f[2][maxl], g[2], cur, pre = 1;
int main()
{
	scanf("%d%d%d", &n, &m, &p);
	fact[0] = a[0] = 1;
	for(int i = 1; i < maxl; ++i)
	{
		fact[i] = (LL)fact[i - 1] * i % p;
		a[i] = a[i - 1] * (m - i + 1LL) % p;
		for(int j = 2; j < i; ++j)
			str[i][j] = (str[i - 1][j - 1] + str[i - 1][j] * (j - 1LL)) % p;
		str[i][i] = 1;
	}
	f[cur][0] = g[cur] = 1;
	for(int i = 1, last = 0, len; i <= n; ++i, last = len)
	{
		scanf("%d", &len);
		pre ^= 1;
		cur ^= 1;
		g[cur] = 0;
		for(int j = 1; j <= len; ++j)
		{
			f[cur][j] = (LL)a[j] * str[len][j] % p * g[pre] % p;
			if(j <= last && (f[cur][j] = (f[cur][j] - (LL)fact[j] * str[len][j] % p * f[pre][j]) % p) < 0)
				f[cur][j] += p;
			if((g[cur] += f[cur][j]) >= p)
				g[cur] -= p;
		}
	}
	printf("%d\n", g[cur]);
	return 0;
}
