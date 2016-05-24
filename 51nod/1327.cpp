#include <stdio.h>
typedef long long LL;
const int maxn = 51, maxm = 201, mod = 1000000007;
int n, m, fact[maxn], iact[maxn], l[maxm], r[maxm], e[maxm], f[maxm][maxn][maxn];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
	{
		int pL, pR;
		scanf("%d%d", &pL, &pR);
		++l[pL];
		++r[m - pR + 1];
		++e[m - pR];
		--e[pL];
	}
	for(int i = m - 1; i > 0; --i)
		e[i] += e[i + 1];
	iact[1] = 1;
	for(int i = 2; i <= n; ++i)
		iact[i] = mod - mod / i * (LL)iact[mod % i] % mod;
	fact[0] = iact[0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	}
	f[0][0][0] = 1;
	for(int i = 0; i < m; ++i)
		for(int j = 0; j <= n; ++j)
			for(int k = 0; k <= n; ++k)
			{
				if(!f[i][j][k])
					continue;
				if(j + 1 - l[i + 1] >= 0 && j + 1 - l[i + 1] <= n) // left
				{
					int coeff = (LL)fact[j + 1] * iact[j + 1 - l[i + 1]] % mod;
					f[i + 1][j + 1 - l[i + 1]][k + r[i + 1]] = (f[i + 1][j + 1 - l[i + 1]][k + r[i + 1]] + (LL)f[i][j][k] * coeff) % mod;
				}
				if(j - l[i + 1] >= 0 && k - 1 + r[i + 1] >= 0) // right
				{
					int coeff = (LL)fact[j] * iact[j - l[i + 1]] % mod * (k + r[i + 1]) % mod;
					f[i + 1][j - l[i + 1]][k - 1 + r[i + 1]] = (f[i + 1][j - l[i + 1]][k - 1 + r[i + 1]] + (LL)f[i][j][k] * coeff) % mod;
				}
				if(j - l[i + 1] >= 0) // default
				{
					int coeff = (LL)fact[j] * iact[j - l[i + 1]] % mod * (e[i + 1] + 1) % mod;
					f[i + 1][j - l[i + 1]][k + r[i + 1]] = (f[i + 1][j - l[i + 1]][k + r[i + 1]] + (LL)f[i][j][k] * coeff) % mod;
				}
			}
	printf("%d\n", f[m][0][0]);
	return 0;
}
