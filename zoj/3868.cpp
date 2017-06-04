#include <cstdio>
typedef long long LL;
const int maxn = 1000001, mod = 998244353;
int t, n, m, mx, f[maxn], ans;
inline int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		(k & 1) && (ret = (LL)ret * x % mod);
	return ret;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		mx = ans = 0;
		scanf("%d%d", &n, &m);
		while(n--)
		{
			int x;
			scanf("%d", &x);
			for( ; mx < x; f[++mx] = 0);
			++f[x];
		}
		for(int i = 1; i <= mx; ++i)
		{
			for(int j = i + i; j <= mx; j += i)
				f[i] += f[j];
			if(f[i])
				f[i] = mod_pow(2, f[i]) - 1;
		}
		for(int i = mx; i >= 1; --i)
		{
			for(int j = i + i; j <= mx; j += i)
				(f[i] -= f[j]) < 0 && (f[i] += mod);
			if(f[i])
				ans = (ans + (LL)f[i] * mod_pow(i, m)) % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
