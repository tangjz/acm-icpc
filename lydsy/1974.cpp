#include <cstdio>
typedef long long LL;
const int maxm = 510, maxd = 10, mod = 999911659;
LL n;
int m, a[maxm], pos[maxm], s[maxm], val, inv[maxd], f[maxd][maxm], ans;
int main()
{
	scanf("%lld%d", &n, &m);
	a[1] = 1 % m;
	pos[a[1]] = 1;
	for(int i = 2; i <= m + 1; ++i)
	{
		a[i] = (a[i - 1] * 10 + 1) % m;
		if(pos[a[i]])
		{
			int beg = pos[a[i]], end = i, len = end - beg;
			for(int j = 1; j < beg && j <= n; ++j)
				++s[a[j]];
			for(int j = 0; j < len && beg + j <= n; ++j)
				s[a[beg + j]] = (s[a[beg + j]] + (n - beg - j) / len + 1) % mod;
			val = n < beg ? a[n] : a[beg + (n - beg) % len];
			--s[val];
			if(s[val] < 0)
				s[val] += mod;
			break;
		}
		pos[a[i]] = i;
	}
	inv[1] = 1;
	for(int i = 2; i < maxd; ++i)
		inv[i] = mod - mod / i * (LL)inv[mod % i] % mod;
	f[0][0] = 1;
	for(int i = 0; i < m; ++i)
	{
		if(!s[i])
			continue;
		for(int j = maxd - 1; j > 0; --j)
		{
			int coeff = 1;
			for(int k = 1; k <= j && coeff; ++k)
			{
				coeff = (LL)coeff * (s[i] - 1 + k) % mod * inv[k] % mod;
				for(int o = 0; o < m; ++o)
					f[j][(o + k * i) % m] = (f[j][(o + k * i) % m] + (LL)coeff * f[j - k][o]) % mod;
			}
		}
	}
	for(int i = 1; i < maxd; ++i)
	{
		int res = val * i % m;
		if(res)
			res = m - res;
		for(int j = 0; i + j < maxd; ++j)
		{
			ans += f[j][res];
			if(ans >= mod)
				ans -= mod;
		}
	}
	printf("%d\n", ans);
	return 0;
}
