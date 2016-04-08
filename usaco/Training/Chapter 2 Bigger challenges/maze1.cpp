/*
ID: tangjin2
LANG: C++
TASK: maze1
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 102, dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1}, INF = 0x3f3f3f3f;
int n, m, e[maxn][maxn], tot, dis[2][maxn][maxn], que[maxn * maxn][2], L, R, ans;
char str[maxn << 1];
void bfs(int x, int y)
{
	L = R = 0;
	dis[tot][x][y] = 1;
	que[R][0] = x;
	que[R++][1] = y;
	while(L < R)
	{
		x = que[L][0];
		y = que[L][1];
		for(int i = 0; i < 4; ++i)
		{
			int nx = x + dx[i], ny = y + dy[i];
			if(!(e[x][y] & (1 << i)) || nx <= 0 || nx > n || ny <= 0 || ny > m || dis[tot][nx][ny])
				continue;
			dis[tot][nx][ny] = dis[tot][x][y] + 1;
			que[R][0] = nx;
			que[R++][1] = ny;
		}
		++L;
	}
	++tot;
}
int main()
{
	freopen("maze1.in", "r", stdin);
	freopen("maze1.out", "w", stdout);
	scanf("%d%d ", &m, &n);
	for(int i = 0; i <= n; ++i)
	{
		if(i > 0)
		{
			fgets(str, maxn, stdin);
			for(int j = 0; j <= m; ++j)
				if(str[j * 2] == ' ')
				{
					e[i][j] |= 2;
					e[i][j + 1] |= 8;
				}
		}
		fgets(str, maxn, stdin);
		for(int j = 1; j <= m; ++j)
			if(str[j * 2 - 1] == ' ')
			{
				e[i][j] |= 4;
				e[i + 1][j] |= 1;
			}
	}
	for(int i = 1; i <= n; ++i)
	{
		if((e[i][1] & 8))
			bfs(i, 1);
		if((e[i][m] & 2))
			bfs(i, m);
	}
	for(int i = 1; i <= m; ++i)
	{
		if((e[1][i] & 1))
			bfs(1, i);
		if((e[n][i] & 4))
			bfs(n, i);
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			ans = max(ans, min(dis[0][i][j], dis[1][i][j]));
	printf("%d\n", ans);
	return 0;
}
