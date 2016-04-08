#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1010, INF = 0x3f3f3f3f;
const int d1[][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
const int d2[][2] = {{1, -2}, {1, 2}, {-1, 2}, {-1, -2}, {2, -1}, {2, 1}, {-2, -1}, {-2, 1}};
int t, n, m, k, x1, y1, f[maxn][maxn][2], x2, y2, g[maxn][maxn][2], que[maxn * maxn * 2], l, r;
bool vis[maxn * maxn * 2];
int idx(int x, int y, int o)
{
	return (x * m + y) * 2 + o;
}
void rid(int id, int &x, int &y, int &o)
{
	o = id & 1;
	id /= 2;
	y = id % m;
	x = id / m;
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d%d", &n, &m, &k);
		l = r = 0;
		memset(vis, 0, sizeof vis);
		memset(f, 0x3f, sizeof f);
		scanf("%d%d", &x1, &y1);
		--x1;
		--y1;
		que[r++] = idx(x1, y1, 0);
		f[x1][y1][0] = 0;
		vis[idx(x1, y1, 0)] = 1;
		while(l < r)
		{
			int id = que[l++], x, y, o;
			rid(id, x, y, o);
			if(f[x][y][o] >= k)
				continue;
			for(int i = 0; i < 8; ++i)
			{
				int xx = x + d1[i][0], yy = y + d1[i][1], idd = idx(xx, yy, o ^ 1);
				if(xx >= 0 && xx < n && yy >= 0 && yy < m && !vis[idd])
				{
					f[xx][yy][o ^ 1] = f[x][y][o] + 1;
					vis[idd] = 1;
					que[r++] = idd;
				}
			}
		}
		l = r = 0;
		memset(vis, 0, sizeof vis);
		memset(g, 0x3f, sizeof g);
		scanf("%d%d", &x2, &y2);
		--x2;
		--y2;
		que[r++] = idx(x2, y2, 0);
		g[x2][y2][0] = 0;
		vis[idx(x2, y2, 0)] = 1;
		while(l < r)
		{
			int id = que[l++], x, y, o;
			rid(id, x, y, o);
			if(g[x][y][o] >= k)
				continue;
			for(int i = 0; i < 8; ++i)
			{
				int xx = x + d2[i][0], yy = y + d2[i][1], idd = idx(xx, yy, o ^ 1);
				if(xx >= 0 && xx < n && yy >= 0 && yy < m && !vis[idd])
				{
					g[xx][yy][o ^ 1] = g[x][y][o] + 1;
					vis[idd] = 1;
					que[r++] = idd;
				}
			}
		}
		int ans = INF;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
			{
				ans = min(ans, max(f[i][j][0], g[i][j][0]));
				ans = min(ans, max(f[i][j][1], g[i][j][1]));
			}
		printf("Case #%d:\n", Case);
		if(ans == INF)
			puts("OH,NO!");
		else
			printf("%d\n", ans);
	}
	return 0;
}
