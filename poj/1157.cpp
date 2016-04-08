#include <cstdio>
#include <cstring>
const int maxn = 101, maxm = 101;
int n, m, f[maxn][maxm], pre[maxn][maxm], ans[maxm];
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		memset(f, 0, sizeof f);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
			{
				scanf("%d", &f[i][j]);
				if(i == 1 || j < i)
					continue;
				int pos = i - 1;
				for(int k = i; k < j; ++k)
					if(f[i - 1][pos] < f[i - 1][k])
						pos = k;
				f[i][j] += f[i - 1][pos];
				pre[i][j] = pos;
			}
		int pos = n;
		for(int i = n + 1; i <= m; ++i)
			if(f[n][pos] < f[n][i])
				pos = i;
		printf("%d\n", f[n][pos]);
//		for(int i = n; i > 0; pos = pre[i--][pos])
//			ans[i] = pos;
//		for(int i = 1; i <= n; ++i)
//			printf("%d%c", ans[i], " \n"[i == n]);
	}
	return 0;
}