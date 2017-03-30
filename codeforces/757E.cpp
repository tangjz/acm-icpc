#include <stdio.h>
typedef long long LL;
const int maxn = 1000101, mod = 1000000007;
int tot, pr[maxn], d[maxn], fact[maxn], iact[maxn];
inline int C(int n, int m)
{
	return (LL)fact[n] * iact[m] % mod * iact[n - m] % mod;
}
int main()
{
	iact[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	fact[0] = iact[0] = 1;
	for(int i = 1; i < maxn; ++i)
	{
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	}
	int t, n, m;
	scanf("%d", &t);
	while(t--)
	{
		int ans = 1;
		scanf("%d%d", &n, &m);
		while(m > 1)
		{
			int pr = d[m], cnt = 0;
			for( ; d[m] == pr; ++cnt, m /= pr);
			ans = (LL)ans * (C(n + cnt, cnt) + C(n + cnt - 1, cnt - 1)) % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}
