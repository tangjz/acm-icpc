#include <stdio.h>
#include <cstring>
typedef long long LL;
const int maxn = 12345679, mod = 1000000007;
int n, tot, pr[maxn >> 3 | 1], d[maxn], phi[maxn], inv[maxn], f[maxn], ans;
inline void mod_inc(int &x, int y)
{
	if((x += y) >= mod)
		x -= mod;
}
int main()
{
	scanf("%d", &n);
	phi[1] = inv[1] = 1;
	for(int i = 2; i <= n; ++i)
	{
		if(!d[i])
		{
			pr[tot++] = d[i] = i;
			phi[i] = i - 1;
		}
		for(int j = 0, k; (k = i * pr[j]) <= n; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
			{
				phi[k] = phi[i] * pr[j];
				break;
			}
			else
				phi[k] = phi[i] * (pr[j] - 1);
		}
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	}
	f[0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		f[i] = (LL)f[i - 1] * (n + 1 - i) % mod * inv[i] % mod;
		ans = (ans - (LL)i * f[i]) % mod;
	}
	for(int i = 1; i <= n; ++i)
	{
		for(int j = i + i; j <= n; j += i)
			mod_inc(f[i], f[j]);
		ans = (ans + (LL)phi[i] * f[i] % mod * f[i]) % mod;
	}
	if((ans = (LL)ans * ((mod + 1) >> 1) % mod) < 0)
		ans += mod;
	printf("%d\n", ans);
	return 0;
}
