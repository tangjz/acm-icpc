#include <cstdio>
const int maxn = 3001, dx[] = {-1, 0, 1, -1, 1, -1, 0, 1}, dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int r, c, n, fa[maxn * maxn * 2], ans;
bool vis[maxn][maxn * 2];
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	scanf("%d%d%d", &r, &c, &n);
	if(c == 1)
	{
		puts("0");
		return 0;
	}
	for(int i = 0; i < r * c * 2; ++i)
		fa[i] = i;
	while(n--)
	{
		int x, y;
		bool flag = 0;
		scanf("%d%d", &x, &y);
		--x, --y;
		for(int i = 0; i < 8; ++i)
		{
			int x1 = x + dx[i], y1 = y + dy[i];
			if(x1 < 0 || x1 >= r)
				continue;
			if(y1 < 0)
				y1 = c * 2 - 1;
			if(!vis[x1][y1])
				continue;
			for(int j = 0; j < 8; ++j)
			{
				int x2 = x + dx[j], y2 = y + c + dy[j];
				if(x2 < 0 || x2 >= r)
					continue;
				if(y2 >= c * 2)
					y2 = 0;
				if(!vis[x2][y2])
					continue;
				if(find(x1 * c * 2 + y1) == find(x2 * c * 2 + y2))
				{
					flag = 1;
					break;
				}
			}
			if(flag)
				break;
		}
		if(!flag)
		{
			++ans;
			for(int i = 0; i < 8; ++i)
			{
				int x1 = x + dx[i], y1 = y + dy[i];
				if(x1 < 0 || x1 >= r)
					continue;
				if(y1 < 0)
					y1 = c * 2 - 1;
				if(vis[x1][y1])
					fa[find(x * c * 2 + y)] = find(x1 * c * 2 + y1);
			}
			for(int i = 0; i < 8; ++i)
			{
				int x1 = x + dx[i], y1 = y + c + dy[i];
				if(x1 < 0 || x1 >= r)
					continue;
				if(y1 >= c * 2)
					y1 = 0;
				if(vis[x1][y1])
					fa[find(x * c * 2 + y + c)] = find(x1 * c * 2 + y1);
			}
			vis[x][y] = vis[x][y + c] = 1;
		}
	}
	printf("%d\n", ans);
	return 0;
}
