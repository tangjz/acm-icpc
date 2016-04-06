#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
const int maxn = 110, maxs = 23333, INF = 0x3f3f3f3f;
typedef pair<int, int> edge;
int t, n, m, s, t1, t2, dis[maxs];
char str[maxn][maxn];
bool vis[maxs];
vector<edge> e[maxs];
priority_queue<edge, vector<edge>, greater<edge> > Q;
int id(int o, int x, int y)
{
	return (o * n + x) * m + y;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
			scanf("%s", str[i]);
		for(int i = 0; i < 2 * n * m; ++i)
			e[i].clear();
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
			{
				if(str[i][j] == '#')
					continue;
				if(str[i][j] == '0')
					s = id(0, i, j);
				if(str[i][j] == '1')
				{
					t1 = id(0, i, j);
					t2 = id(1, i, j);
				}
				if(str[i][j] == '@')
				{
					e[id(0, i, j)].push_back(make_pair(0, id(1, i, j)));
					e[id(1, i, j)].push_back(make_pair(0, id(0, i, j)));
				}
				if(str[i][j] != '3')
				for(int d = 0; d < 4; ++d)
				{
					int x = i + dx[d], y = j + dy[d];
					if(x >= 0 && x < n && y >= 0 && y < m && (str[x][y] != '3' && str[x][y] != '#'))
						e[id(0, i, j)].push_back(make_pair(1, id(0, x, y)));
				}
				if(str[i][j] != '2')
				for(int d = 0; d < 4; ++d)
				{
					int x = i + dx[d], y = j + dy[d];
					if(x >= 0 && x < n && y >= 0 && y < m && (str[x][y] != '2' && str[x][y] != '#'))
						e[id(1, i, j)].push_back(make_pair(1, id(1, x, y)));
				}
			}
		while(!Q.empty())
			Q.pop();
		memset(dis, 0x3f, sizeof dis);
		memset(vis, 0, sizeof vis);
		dis[s] = 0;
		Q.push(make_pair(dis[s], s));
		while(!Q.empty())
		{
			int u = Q.top().second;
			Q.pop();
			if(vis[u])
				continue;
			vis[u] = 1;
			for(vector<edge>::iterator it = e[u].begin(); it != e[u].end(); ++it)
			{
				int &v = it -> second, &w = it -> first;
				if(dis[v] > dis[u] + w)
				{
					dis[v] = dis[u] + w;
					Q.push(make_pair(dis[v], v));
				}
			}
		}
		if(dis[t1] == INF && dis[t2] == INF)
			puts("-1");
		else
			printf("%d\n", min(dis[t1], dis[t2]));
	}
	return 0;
}
