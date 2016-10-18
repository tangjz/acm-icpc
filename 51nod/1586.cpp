#include <stdio.h>
const int maxn = 1000001;
int n, q, d[maxn];
long long c[maxn];
int main()
{
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; ++i)
		for(int j = i; j <= n; j += i)
			++d[j];
	while(q--)
	{
		int t, x, y;
		scanf("%d%d", &t, &x);
		if(t == 1)
		{
			scanf("%d", &y);
			for(int i = 1, j = x; j <= n; ++i, j += x)
				c[j] += (long long)d[i] * y;
		}
		else
			printf("%lld\n", c[x]);
	}
	return 0;
}
