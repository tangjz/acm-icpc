#include <stdio.h>
typedef long long LL;
const int maxn = 1000001;
int t, n, mod, f[maxn], inv[maxn], ans;
inline int mod_inv(int x)
{
	return x <= n ? inv[x] : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
inline void mod_inc(int &x, int y)
{
	(x += y) >= mod && (x -= mod);
}
int main()
{
    scanf("%d", &t);
    while(t--)
	{
	    scanf("%d%d", &n, &mod);
		f[1] = inv[1] = 1;
		for(int i = 2; i <= n; ++i)
		{
			mod_inc(f[i] = f[i - 2], f[i - 1]);
			mod_inc(f[i], f[i - 1]);
			inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
		}
		for(int i = 2; i <= n; ++i)
			for(int j = i + i, val = mod_inv(f[i]); j <= n; j += i)
				f[j] = (LL)f[j] * val % mod;
		ans = 1;
		for(int i = 2, prd = 1; i <= n; ++i)
		{
			prd = (LL)prd * f[i] % mod;
			ans = (ans + (LL)i * prd) % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
