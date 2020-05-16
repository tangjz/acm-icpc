#include <stdio.h>
typedef long long LL;
const int maxn = 16;
int t, n, x0, f[maxn];
LL g[maxn], r;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &x0);
		for(int i = 0; i <= n; ++i)
			scanf("%d", f + i);
		r = 0;
		for(int i = n; i >= 0; --i)
			r = r * x0 + f[i];
		printf("%I64d\n", r);
		for(int i = 0; i < n; ++i)
		{
			g[i] = ((i ? g[i - 1] : r) - f[i]) / x0;
			printf("%I64d%c", g[i], " \n"[i == n - 1]);
		}
	}
	return 0;
}