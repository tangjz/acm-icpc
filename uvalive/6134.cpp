#include <cstdio>
int n, m, ans;
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		for(ans = 0; n <= m; ++n)
		{
			bool vis[10] = {}, flag = 1;
			for(int i = n; i && flag; i /= 10)
			{
				flag &= !vis[i % 10];
				vis[i % 10] = 1;
			}
			ans += flag;
		}
		printf("%d\n", ans);
	}
	return 0;
}
