#include <cstdio>
#include <cstring>
const int maxn = 55, dx[] = {0, 1, 0, -1}, dy[] = {-1, 0, 1, 0};
int n, m;
char str[maxn][maxn];
bool vis[maxn][maxn];
bool dfs(int x, int y, int o)
{
	if(vis[x][y])
		return 0;
	vis[x][y] = 1;
	bool flag = 1;
	for(int d = 0; d < 4 && flag; ++d)
	{
		if(d + o == 3)
			continue;
		int xx = x + dx[d], yy = y + dy[d];
		if(xx >= 0 && xx < n && yy >= 0 && yy < m && str[x][y] == str[xx][yy])
			flag &= dfs(xx, yy, d);
	}
	return flag;
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		for(int i = 0; i < n; ++i)
			scanf("%s", str[i]);
		memset(vis, 0, sizeof vis);
		bool flag = 1;
		for(int i = 0; i < n && flag; ++i)
			for(int j = 0; j < m && flag; ++j)
				if(!vis[i][j])
					flag &= dfs(i, j, -1);
		puts(flag ? "No" : "Yes");
	}
	return 0;
}
