#include <stdio.h>
const int maxn = 1001;
int n, m, t, a[maxn], ans;
int main()
{
	while(scanf("%d%d%d", &n, &m, &t) == 3)
	{
		ans = 0;
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		while(t--)
		{
			int res = 0, pos = -1;
			for(int i = 0, sum = 0; i < n; ++i)
			{
				sum += a[i];
				if(i >= m)
					sum -= a[i - m];
				if(res < sum)
				{
					res = sum;
					pos = i;
				}
			}
			ans += res;
			for(int i = pos + 1, d = pos + 1 < m ? pos + 1 : m; i < n; ++i)
				a[i - d] = a[i];
			n -= pos + 1 < m ? pos + 1 : m;
		}
		printf("%d\n", ans);
	}
	return 0;
}

