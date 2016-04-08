/*
ID: tangjin2
LANG: C++
TASK: ttwo
*/
#include <cstdio>
const int maxn = 10, dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
int Fx, Fy, Fd, Cx, Cy, Cd;
char str[maxn][maxn + 1];
bool vis[maxn * maxn * 4][maxn * maxn * 4];
void change(int &x, int &y, int &d)
{
	int nx = x + dx[d], ny = y + dy[d];
	if(0 <= nx && nx < maxn && 0 <= ny && ny < maxn && str[nx][ny] != '*')
	{
		x = nx;
		y = ny;
	}
	else
		d = (d + 1) & 3;
}
int main()
{
	freopen("ttwo.in", "r", stdin);
	freopen("ttwo.out", "w", stdout);
	for(int i = 0; i < maxn; ++i)
	{
		scanf("%s", str[i]);
		for(int j = 0; j < maxn; ++j)
			if(str[i][j] == 'F')
			{
				Fx = i;
				Fy = j;
				Fd = 0;
			}
			else if(str[i][j] == 'C')
			{
				Cx = i;
				Cy = j;
				Cd = 0;
			}
	}
	for(int i = 1; ; ++i)
	{
		vis[(Fx * maxn + Fy) << 2 | Fd][(Cx * maxn + Cy) << 2 | Cd] = 1;
		change(Fx, Fy, Fd);
		change(Cx, Cy, Cd);
		if(Fx == Cx && Fy == Cy)
		{
			printf("%d\n", i);
			break;
		} else if(vis[(Fx * maxn + Fy) << 2 | Fd][(Cx * maxn + Cy) << 2 | Cd])
		{
			puts("0");
			break;
		}
	}
	return 0;
}
