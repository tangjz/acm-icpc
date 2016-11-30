#include <stdio.h>
typedef long long LL;
const int maxn = 16, mod = 1000000007;
int inv[maxn + 1], t, n, m, lim[maxn], sum, all, leq, eq;
int mod_inv(int x)
{
	return x <= maxn ? inv[x] : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
int main()
{
	inv[1] = 1;
	for(int i = 2; i <= maxn; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	scanf("%d", &t);
	while(t--)
	{
		sum = 0;
		all = 1;
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
		{
			int L, R;
			scanf("%d%d", &L, &R);
			lim[i] = R - L + 1;
			sum -= L;
			all = (LL)all * lim[i] % mod;
		}
		scanf("%d", &m);
		for(int i = n; i < n + m; ++i)
		{
			int L, R;
			scanf("%d%d", &L, &R);
			lim[i] = R - L + 1;
			sum += R;
			all = (LL)all * lim[i] % mod;
		}
		n += m;
		leq = 0, eq = 0;
		for(int i = 0; i < 1 << n; ++i)
		{
			int sei = 1, val = sum;
			for(int j = 0; j < n; ++j)
				if((i >> j) & 1)
				{
					sei = mod - sei;
					val -= lim[j];
				}
			if(val < 0)
				continue;
			for(int j = 1; j < n; ++j)
				sei = (LL)sei * (val + j) % mod * inv[j] % mod;
			if((eq += sei) >= mod)
				eq -= mod;
			sei = (LL)sei * (val + n) % mod * inv[n] % mod;
			if((leq += sei) >= mod)
				leq -= mod;
		}
		all = mod_inv(all);
		leq = (LL)leq * all % mod;
		eq = (LL)eq * all % mod;
		int les = leq < eq ? leq - eq + mod : leq - eq, gre = 1 < leq ? 1 - leq + mod : 1 - leq;
		printf("%d %d %d\n", gre, eq, les);
	}
	return 0;
}
