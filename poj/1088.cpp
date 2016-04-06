#include <cstdio>
const int maxn = 101, dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
int n, m, a[maxn][maxn], f[maxn][maxn], ans;
void upd(int &x, int y)
{
	if(x < y)
		x = y;
}
int dfs(int x, int y)
{
	if(f[x][y])
		return f[x][y];
	f[x][y] = 1;
	for(int i = 0; i < 4; ++i)
	{
		int xx = x + dx[i], yy = y + dy[i];
		if(xx > 0 && xx <= n && yy > 0 && yy <= m && a[xx][yy] < a[x][y])
			upd(f[x][y], dfs(xx, yy) + 1);
	}
	return f[x][y];
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			scanf("%d", &a[i][j]);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			upd(ans, dfs(i, j));
	printf("%d\n", ans);
	return 0;
}
