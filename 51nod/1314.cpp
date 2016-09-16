#include <cstdio>
const int maxn = 51;
int n, ans;
char e[maxn][maxn + 1];
int dfs(int u, int fa, int &cost)
{
	int ret = 0, cnt = 0;
	for(int v = 0; v < n; ++v)
		if(v != fa && e[u][v] == 'Y')
		{
			ret += dfs(v, u, cost);
			++cnt;
		}
	if(ret < cnt)
	{
		cost += cnt - ret - 1;
		ret = cnt - 1;
	}
	return ret > 0;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%s", e[i]);
	ans = n > 1 ? n : 0;
	for(int i = 0; i < n; ++i)
	{
		int tmp = 1;
		dfs(i, -1, tmp);
		if(ans > tmp)
			ans = tmp;
	}
	printf("%d\n", ans);
	return 0;
}
