#include <cstdio>
const int maxm = 36;
int tot, p[maxm], f[maxm], c[maxm], n, a, b;
unsigned long long ans;
int main()
{
	for(int i = 2; i < maxm; ++i)
	{
		if(!f[i])
			p[tot++] = f[i] = i;
		for(int j = 0; j < tot && i * p[j] < maxm; ++j)
		{
			f[i * p[j]] = p[j];
			if(i % p[j] == 0)
				break;
		}
	}
	scanf("%d%d%d", &n, &a, &b);
	++c[n + a], --c[n], --c[a];
	++c[n + b], --c[n], --c[b];
	for(int i = maxm - 2; i > 1; --i)
		c[i] += c[i + 1];
	for(int i = maxm - 1; i > 1; --i)
		if(f[i] != i)
		{
			c[f[i]] += c[i];
			c[i / f[i]] += c[i];
		}
	ans = 1;
	for(int i = 0; i < tot; ++i)
		for(int j = 0; j < c[p[i]]; ++j)
			ans *= p[i];
	printf("%llu\n", ans);
	return 0;
}
