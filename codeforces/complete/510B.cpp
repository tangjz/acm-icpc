#include <cstdio>
const int dx[] = {-1, 0, 0, 1}, dy[] = {0, 1, -1, 0};
int n, m;
char str[51][51];
bool vis[51][51], flag;
void dfs(int x, int y, int d)
{
	vis[x][y] = 1;
	for(int i = 0; i < 4; ++i)
	{
		if(i + d == 3)
			continue;
		int xx = x + dx[i], yy = y + dy[i];
		if(xx >= 0 && xx < n && yy >= 0 && yy < m && str[x][y] == str[xx][yy])
		{
			if(vis[xx][yy])
				flag = 1;
			else
				dfs(xx, yy, i);
		}
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%s", str + i);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			if(!vis[i][j])
				dfs(i, j, 4);
	puts(flag ? "Yes" : "No");
	return 0;
}
