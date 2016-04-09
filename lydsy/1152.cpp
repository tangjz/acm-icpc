#include <stdio.h>
#include <cstring>
const int maxm = 100001, mod = 10000;
int n, t, pw[maxm], m, a[maxm], f[maxm], ans;
int main()
{
	scanf("%d%d", &n, &t);
	pw[0] = 1;
	for(int i = 1; i < maxm; ++i)
		pw[i] = pw[i - 1] * n % mod;
	while(t--)
	{
		scanf("%d", &m);
		for(int i = 0; i < m; ++i)
			scanf("%d", a + i);
		for(int i = 1, j = 0; i < m; ++i)
		{
			while(j && a[i] != a[j])
				j = f[j];
			f[i + 1] = a[i] == a[j] ? ++j : j;
		}
		ans = 0;
		for(int i = m; i; i = f[i])
		{
			ans += pw[i];
			if(ans >= mod)
				ans -= mod;
		}
		printf("%04d\n", ans);
	}
	return 0;
}

