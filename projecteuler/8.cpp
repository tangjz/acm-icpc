#include <stdio.h>
const int maxn = 1001;
int t, n, m, a[maxn], ans;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
			scanf("%1d", a + i);
		ans = 0;
		for(int i = 0; i + m <= n; ++i)
		{
			int tmp = 1;
			for(int j = 0; j < m; ++j)
				tmp *= a[i + j];
			if(ans < tmp)
				ans = tmp;
		}
		printf("%d\n", ans);
	}
	return 0;
}
