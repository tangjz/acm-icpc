#include <cstdio>
#include <cstring>
const int maxn = 8, maxk = 65, mod = 1000000007;
typedef long long LL;
int t, n, m, k, fact[maxk], inv[maxk], f[2][maxk][1 << maxn], ans;
int C(int n, int m)
{
	return (LL)fact[n] * inv[m] % mod * inv[n - m] % mod;
}
void inc(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
void dec(int &x, int y)
{
	x -= y;
	if(x < 0)
		x += mod;
}
int main()
{
	fact[0] = 1;
	for(int i = 1; i < maxk; ++i)
		fact[i] = (LL)fact[i - 1] * i % mod;
	inv[1] = 1;
	for(int i = 2; i < maxk; ++i)
		inv[i] = (LL)inv[mod % i] * (mod - mod / i) % mod;
	inv[0] = 1;
	for(int i = 1; i < maxk; ++i)
		inv[i] = (LL)inv[i - 1] * inv[i] % mod;
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d%d", &n, &m, &k);
		memset(f[0], 0, sizeof f[0]);
		f[0][0][1] = 1;
		for(int i = 0, o = 0; i < n; ++i)
			for(int j = 0; j < m; ++j, o ^= 1)
			{
				memset(f[o ^ 1], 0, sizeof f[o ^ 1]);
				for(int t = 0; t <= k; ++t)
					for(int msk = 0; msk < (1 << m); ++msk)
					{
						if(!f[o][t][msk])
							continue;
						if(t < k)
							inc(f[o ^ 1][t + 1][msk ^ (msk & (1 << j))], f[o][t][msk]);
						if((msk & (1 << j)) || (j > 0 && (msk & (1 << j - 1))))
							inc(f[o ^ 1][t][msk | (1 << j)], f[o][t][msk]);
						else
							inc(f[o ^ 1][t][msk ^ (msk & (1 << j))], f[o][t][msk]);
					}
			}
		ans = 0;
		for(int i = 0; i <= k; ++i)
		{
			inc(ans, C(n * m, i));
			for(int msk = 0; msk < (1 << m); ++msk)
				if(msk & (1 << m - 1))
					dec(ans, f[(n * m) & 1][i][msk]);
		}
		printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}
