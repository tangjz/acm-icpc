#include <stdio.h>
typedef long long LL;
const int maxn = 100001;
int t, n, q, mod, a[maxn], b[maxn], ib, ab;
LL m;
int mod_pow(int x, LL k)
{
	int ret = 1;
	for( ; k; k >>= 1, x = (LL)x * x % mod)
		if(k & 1)
			ret = (LL)ret * x % mod;
	return ret;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d", &n, &q, &mod);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		for(int i = 0; i < n; ++i)
			scanf("%d", b + i);
		ib = ab = 0;
		for(int i = 0; i < n; ++i)
		{
			ib = (ib + (LL)i * b[i]) % mod;
			ab = (ab + (LL)a[i] * b[i]) % mod;
		}
		while(q--)
		{
			scanf("%lld", &m);
			printf("%d\n", (int)(m < n ? m % mod : (LL)a[m % n] * ib % mod * mod_pow(ab, m / n - 1) % mod));
		}
	}
	return 0;
}
