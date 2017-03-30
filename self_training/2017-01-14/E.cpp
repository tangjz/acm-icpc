#include <stdio.h>
#include <cstring>
const int maxn = 100001, maxd = 83, maxs = 11;
int t, n, q, dig[maxd], ans[maxn];
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		memset(dig, -1, sizeof dig);
		scanf("%d%d", &n, &q);
		for(int i = 1; i <= n; ++i)
		{
			int x;
			scanf("%d", &x);
			char buf[maxs];
			sprintf(buf, "%d", x);
			int sum = 0;
			for(int j = 0; buf[j]; ++j)
				sum += buf[j] - '0';
			ans[i] = dig[sum];
			if(dig[sum] < x)
				dig[sum] = x;
		}
		printf("Case #%d:\n", Case);
		while(q--)
		{
			int x;
			scanf("%d", &x);
			printf("%d\n", ans[x]);
		}
	}
	return 0;
}
