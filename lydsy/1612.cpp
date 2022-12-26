/*
 * 传递闭包，一个人的排名确定当且仅当它前后的人数为n - 1
 */
#include <cstdio>
const int maxn = 101;
int n, m, ans;
bool g[maxn][maxn];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0, u, v; i < m; ++i)
	{
		scanf("%d%d", &u, &v);
		g[u][v] = 1;
	}
	for(int k = 1; k <= n; ++k)
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				g[i][j] |= g[i][k] & g[k][j];
	for(int i = 1; i <= n; ++i)
	{
		int cnt = 0;
		for(int j = 1; j <= n; ++j)
			cnt += g[i][j] | g[j][i];
		if(cnt == n - 1) ++ans;
	}
	printf("%d\n", ans);
	return 0;
}
