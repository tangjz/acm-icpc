#include <cstdio>
#include <cstring>
const int maxn = 1001, maxs = 20001;
int n, g[maxn][maxn], tot, tmp[maxs][2], cnt[2], ans[2][maxs][2];
void dfs(int l, int r, int flag)
{
	if(r - l + 1 <= 2)
		return;
	int mid = l + r >> 1;
	tot = 0;
	for(int i = l; i < mid; ++i)
		for(int j = r; j > mid; --j)
			if(g[i][j])
			{
				tmp[tot][0] = i;
				tmp[tot++][1] = j;
			}
	if(tot)
	{
		int last[2] = {tmp[0][0], tmp[0][1]};
		for(int i = 0; i < tot; ++i)
		{
			int now = 0;
			if(i == tot - 1)
				now = mid;
			else if(tmp[i][0] == tmp[i + 1][0])
				now = tmp[i + 1][1];
			else
				now = tmp[i + 1][0];
			g[last[0]][last[1]] = g[last[1]][last[0]] = 0;
			g[0][now] = g[now][0] = 1;
			if(!flag)
			{
				ans[0][cnt[0]][0] = last[0];
				ans[0][cnt[0]++][1] = last[1];
			}
			else
			{
				ans[1][cnt[1]][0] = 0;
				ans[1][cnt[1]++][1] = now;
			}
			if(i != tot - 1)
				if(tmp[i][0] == tmp[i + 1][0])
					last[1] = tmp[i + 1][1];
				else
					last[0] = tmp[i + 1][0];
		}
	}
	dfs(l, mid, flag);
	dfs(mid, r, flag);
}
int main()
{
	scanf("%d", &n);
	for(int i = 3; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		--u;
		--v;
		g[u][v] = g[v][u] = 1;
	}
	dfs(1, n - 1, 0);
	memset(g, 0, sizeof g);
	for(int i = 3; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		--u;
		--v;
		g[u][v] = g[v][u] = 1;
	}
	dfs(1, n - 1, 1);
	printf("%d\n", cnt[0] + cnt[1]);
	for(int i = 0; i < cnt[0]; ++i)
		printf("%d %d\n", ans[0][i][0] + 1, ans[0][i][1] + 1);
	for(int i = cnt[1] - 1; i >= 0; --i)
		printf("%d %d\n", ans[1][i][0] + 1, ans[1][i][1] + 1);
	return 0;
}
