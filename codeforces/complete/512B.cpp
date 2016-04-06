#include <cstdio>
#include <cstring>
const int maxn = 301, maxk = 10, maxs = 1 << 9, INF = 0x3f3f3f3f;
int n, a[maxn], c[maxn], tot, fact[maxk], f[maxs], ans = INF;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = 1; i <= n; ++i)
		scanf("%d", c + i);
	for(int i = 1, j, k; i <= n; ++i)
	{
		tot = 0;
		for(j = 2, k = a[i]; j * j <= k; ++j)
			if(k % j == 0)
			{
				fact[tot++] = j;
				while(k % j == 0)
					k /= j;
			}
		if(k > 1)
			fact[tot++] = k;
		memset(f, 0x3f, sizeof f);
		f[(1 << tot) - 1] = c[i];
		for(j = 1; j <= n; ++j)
		{
			int mask = 0;
			for(k = 0; k < tot; ++k)
				if(a[j] % fact[k] == 0)
					mask |= 1 << k;
			for(int s = (1 << tot) - 1; s >= 0; --s)
				if(f[s & mask] > f[s] + c[j])
					f[s & mask] = f[s] + c[j];
		}
		if(ans > f[0])
			ans = f[0];
	}
	if(ans == INF)
		puts("-1");
	else
		printf("%d\n", ans);
	return 0;
}
