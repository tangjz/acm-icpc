#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 3010;
int n, m, st[4], ll[2], dis[maxn][maxn], que[maxn], l, r, ans;
vector<int> e[maxn];
bool vis[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	scanf("%d%d%d", &st[0], &st[1], &ll[0]);
	scanf("%d%d%d", &st[2], &st[3], &ll[1]);
	for(int i = 1; i <= n; ++i)
	{
		memset(vis, 0, sizeof vis);
		l = r = 0;
		que[r++] = i;
		vis[i] = 1;
		while(l < r)
		{
			int u = que[l++];
			for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
				if(!vis[*it])
				{
					int &v = *it;
					dis[i][v] = dis[i][u] + 1;
					que[r++] = v;
					vis[v] = 1;
				}
		}
	}
	if(dis[st[0]][st[1]] > ll[0] || dis[st[2]][st[3]] > ll[1])
	{
		puts("-1");
		return 0;
	}
	ans = min(dis[st[0]][st[1]] + dis[st[2]][st[3]], m);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
		{
			if(dis[st[0]][i] + dis[i][j] + dis[j][st[1]] <= ll[0] && dis[st[2]][i] + dis[i][j] + dis[j][st[3]] <= ll[1])
				ans = min(ans, dis[st[0]][i] + dis[i][j] + dis[j][st[1]] + dis[st[2]][i] + dis[j][st[3]]);
			if(dis[st[0]][i] + dis[i][j] + dis[j][st[1]] <= ll[0] && dis[st[2]][j] + dis[j][i] + dis[i][st[3]] <= ll[1])
				ans = min(ans, dis[st[0]][i] + dis[i][j] + dis[j][st[1]] + dis[st[2]][j] + dis[i][st[3]]);
		}
	printf("%d\n", m - ans);
	return 0;
}
