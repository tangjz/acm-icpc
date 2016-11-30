#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxm = 2005, mod = 1000000007;
int t, n, m, q, c[maxm][maxm], iact[maxm], tot, prime[maxm], f[maxm], pre[maxm], suf[maxm], ans;
int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
int mod_inv(int x)
{
	return x <= 1 ? x : mod - mod / x * (LL)mod_inv(mod % x) % mod;
}
int main()
{
	iact[1] = 1;
	for(int i = 2; i < maxm; ++i)
		iact[i] = mod - mod / i * (LL)iact[mod % i] % mod;
	iact[0] = 1;
	for(int i = 1; i < maxm; ++i)
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	for(int i = 0; i < maxm; ++i)
	{
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			if((c[i][j] = c[i - 1][j - 1] + c[i - 1][j]) >= mod)
				c[i][j] -= mod;
	}
	LL tn, tq;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%lld%lld", &m, &tn, &tq);
		if((q = tq % mod) == 1)
		{
			tot = 0;
			memset(f + 1, 0, (m + 1) * sizeof(int));
			f[1] = 1;
			for(int i = 2; i <= m + 1; ++i)
			{
				if(!f[i])
				{
					prime[tot++] = i;
					f[i] = mod_pow(i, m);
				}
				for(int j = 0, o; j < tot && (o = i * prime[j]) <= m + 1; ++j)
				{
					f[o] = (LL)f[i] * f[prime[j]] % mod;
					if(i % prime[j] == 0)
						break;
				}
			}
			for(int i = 2; i <= m + 1; ++i)
				if((f[i] += f[i - 1]) >= mod)
					f[i] -= mod;
			if(tn <= m + 1)
			{
				printf("%d\n", f[(int)tn]);
				continue;
			}
			pre[0] = tn % mod;
			for(int i = 1; i <= m + 1; ++i)
				pre[i] = (tn - i) % mod * pre[i - 1] % mod;
			suf[m + 1] = (tn - m - 1) % mod;
			for(int i = m; i >= 0; --i)
				suf[i] = (tn - i) % mod * suf[i + 1] % mod;
			ans = 0;
			for(int i = 0; i <= m + 1; ++i)
			{
				int tmp = (LL)f[i] * iact[i] % mod * iact[m + 1 - i] % mod;
				if(i > 0)
					tmp = (LL)tmp * pre[i - 1] % mod;
				if(i <= m)
					tmp = (LL)tmp * suf[i + 1] % mod;
				if(((m + 1 - i) & 1) && tmp > 0)
					tmp = mod - tmp;
				if((ans += tmp) >= mod)
					ans -= mod;
			}
			printf("%d\n", ans);
		}
		else if(q > 0)
		{
			n = tn % mod;
			int sei = mod_pow(q, (tn + 1) % (mod - 1)), iei = mod_inv(q - 1);
			if((f[0] = (LL)(sei - q) * iei % mod) < 0)
				f[0] += mod;
			for(int i = 1, coeff = n; i <= m; ++i, coeff = (LL)coeff * n % mod)
			{
				f[i] = (LL)coeff * sei % mod;
				for(int j = 0; j < i; ++j)
				{
					int tmp = (LL)c[i][j] * f[j] % mod;
					if(((i - j) & 1) && tmp > 0)
						tmp = mod - tmp;
					if((f[i] += tmp) >= mod)
						f[i] -= mod;
				}
				f[i] = (LL)f[i] * iei % mod;
			}
			printf("%d\n", f[m]);
		}
		else
			puts("0");
	}
	return 0;
}
