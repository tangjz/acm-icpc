#include <cstdio>
#include <cstring>
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
char g[11][11];
bool checkmate(int x, int y)
{
	for(int i = 0; i < 4; ++i)
	{
		if(dx[i])
		{
			if((!g[x + dx[i]][y - 1] && g[x + dx[i] + dx[i]][y - 1] == 'H')
			|| (!g[x + dx[i]][y + 1] && g[x + dx[i] + dx[i]][y + 1] == 'H'))
				return 1;
		}
		else
		{
			if((!g[x - 1][y + dy[i]] && g[x - 1][y + dy[i] + dy[i]] == 'H')
			|| (!g[x + 1][y + dy[i]] && g[x + 1][y + dy[i] + dy[i]] == 'H'))
				return 1;
		}
		bool flag = 0;
		int xx = x + dx[i], yy = y + dy[i];
		while(xx > 0 && xx <= 10 && yy > 0 && yy <= 9)
		{
			if(!flag)
			{
				if(g[xx][yy] == 'R' || g[xx][yy] == 'G')
					return 1;
			}
			else
			{
				if(g[xx][yy] == 'C')
					return 1;
			}
			if(g[xx][yy])
			{
				if(!flag)
					flag = 1;
				else
					break;
			}
			xx += dx[i];
			yy += dy[i];
		}
	}
	return 0;
}
int main()
{
	int n, x, y, xx, yy;
	char op[2];
	while(scanf("%d%d%d", &n, &x, &y) == 3 && n && x && y)
	{
		memset(g, 0, sizeof g);
		while(n--)
		{
			scanf("%s%d%d", op, &xx, &yy);
			g[xx][yy] = op[0];
		}
		bool flag = 1;
		for(int i = 0; i < 4; ++i)
		{
			xx = x + dx[i];
			yy = y + dy[i];
			if(xx < 1 || xx > 3 || yy < 4 || yy > 6)
				continue;
			if(!checkmate(xx, yy))
			{
				flag = 0;
				break;
			}
		}
		puts(flag ? "YES" : "NO");
	}
	return 0;
}