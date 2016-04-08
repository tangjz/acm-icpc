#include <cstdio>
#include <cstring>
const int maxn = 510, dx[] = {0, 1, -1, 0}, dy[] = {1, 0, 0, -1};
int t, n, m, q, que[maxn * maxn], l, r, ans;
bool vis[maxn][maxn];
int idx(int x, int y)
{
	return x * m + y;
}
void rid(int o, int &x, int &y)
{
	x = o / m;
	y = o % m;
}
bool vaild(int x, int y)
{
	return x >= 0 && x < n && y >= 0 && y < m;
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		printf("Case #%d:\n", Case);
		scanf("%d%d%d", &n, &m, &q);
		memset(vis, 0, sizeof vis);
		l = r = ans = 0;
		for(int i = 0, x, y; i < q; ++i)
		{
			scanf("%d%d", &x, &y);
			--x, --y;
			if(vis[x][y])
				continue;
			vis[x][y] = 1;
			for(int d = 0; d < 4; ++d)
			{
				int xx = x + dx[d], yy = y + dy[d], cnt = 0, qque[4] = {};
				if(!vaild(xx, yy) || vis[xx][yy])
					continue;
				for(int dd = 0; dd < 4; ++dd)
				{
					int xxx = xx + dx[dd], yyy = yy + dy[dd];
					if(vaild(xxx, yyy) && vis[xxx][yyy])
					{
						qque[cnt++] = dd;
					}
				}
				if(cnt > 2 || cnt == 2 && qque[0] + qque[1] != 3)
				{
					vis[xx][yy] = 1;
					que[r++] = idx(xx, yy);
				}
			}
		}
		while(l < r)
		{
			int o = que[l++], x, y;
			rid(o, x, y);
			for(int d = 0; d < 4; ++d)
			{
				int xx = x + dx[d], yy = y + dy[d], cnt = 0, qque[4] = {};
				if(!vaild(xx, yy) || vis[xx][yy])
					continue;
				for(int dd = 0; dd < 4; ++dd)
				{
					int xxx = xx + dx[dd], yyy = yy + dy[dd];
					if(vaild(xxx, yyy) && vis[xxx][yyy])
					{
						qque[cnt++] = dd;
					}
				}
				if(cnt > 2 || cnt == 2 && qque[0] + qque[1] != 3)
				{
					vis[xx][yy] = 1;
					que[r++] = idx(xx, yy);
				}
			}
		}
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				if(vis[i][j])
					++ans;
		printf("%d\n", ans);
	}
	return 0;
}
