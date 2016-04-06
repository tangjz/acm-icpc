#include <cstdio>
#include <cstring>
const int maxn = 1001;
int t, n, deg[maxn][2], ans;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		memset(deg, 0, sizeof deg);
		for(int i = 0; i < n; ++i)
			for(int j = i + 1; j < n; ++j)
			{
				int x;
				scanf("%d", &x);
				++deg[i][x];
				++deg[j][x];
			}
		ans = n * (n - 1) * (n - 2) / 3;
		for(int i = 0; i < n; ++i)
			ans -= deg[i][0] * deg[i][1];
		printf("%d\n", ans >> 1);
	}
	return 0;
}
