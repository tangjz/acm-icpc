#include <cstdio>
typedef long long LL;
const int maxn = 100001, mod = 1000000009, sq5 = 383008016;
int inv[maxn + 1], pw[maxn], iw[maxn];
int t, m, ans;
LL n;
int mod_inv(int x)
{
	return x < maxn ? inv[x] : mod - mod / x * (LL)mod_inv(mod % x) % mod;
}
int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
int main()
{
	inv[1] = 1;
	for(int i = 2; i < maxn; ++i)
		inv[i] = mod - mod / i * (LL)inv[mod % i] % mod;
	pw[0] = iw[0] = 1;
	pw[1] = mod - (1LL + sq5) * inv[2] % mod;
	iw[1] = mod_inv(pw[1]);
	for(int i = 2; i < maxn; ++i)
	{
		pw[i] = (LL)pw[i - 1] * pw[1] % mod;
		iw[i] = (LL)iw[i - 1] * iw[1] % mod;
	}
	scanf("%d", &t);
	while(t--)
	{
		ans = 0;
		scanf("%lld%d", &n, &m);
		int nv = n % mod, ne = (n + 1) % (mod - 1), ce = sq5, ie = mod_inv(sq5);
		for(int i = 0, coeff = 1; i <= m; ++i)
		{
			int val = i <= m >> 1 ? iw[m - (i << 1)] : pw[(i << 1) - m];
			if((i & 1) && val)
				val = mod - val;
			val = val == 1 ? nv : (LL)(mod_pow(val, ne) - val) * mod_inv(val - 1) % mod;
			if(((m - i) & 1) && val)
				val = mod - val;
			ans = (ans + (LL)coeff * val) % mod;
			coeff = (LL)coeff * (m - i) % mod * inv[i + 1] % mod;
			ce = (LL)ce * ie % mod;
		}
		ans = (LL)ans * ce % mod;
		if(ans < 0)
			ans += mod;
		printf("%d\n", ans);
	}
	return 0;
}
