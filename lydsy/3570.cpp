#include <cmath>
#include <stdio.h>
const int maxn = 100000, mx = 1 << 16;
int n, m, bit[maxn + 1];
int main()
{
	scanf("%d%d", &n, &m);
	while(n--)
	{
		int x;
		scanf("%d%*d%*d", &x);
		++bit[x];
	}
	for(int i = 1; i <= maxn; ++i)
	{
		int j = i + (i & -i);
		if(j <= maxn)
			bit[j] += bit[i];
	}
	scanf("%d", &n);
	while(n--)
	{
		int tp, x, y;
		scanf("%d", &tp);
		if(tp == 0)
		{
			scanf("%d%*d%*d", &x);
			for( ; x <= maxn; x += x & -x)
				++bit[x];
		}
		else
		{
			scanf("%d%d", &x, &y);
			tp = 0;
			for(int i = mx; i > 0; i >>= 1)
			{
				tp |= i;
				if(tp <= maxn && bit[tp] < y)
					y -= bit[tp];
				else
					tp ^= i;
			}
			++tp;
			printf("%.3f\n", sqrt((long long)tp * tp + 2LL * m * x));
		}
	}
	return 0;
}
