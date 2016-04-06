#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef pair<int, int> edge;
const int maxn = 1001;
int n, m, x, dist[2][maxn], ans;
bool vis[2][maxn];
vector<edge> g[2][maxn];
priority_queue<edge, vector<edge>, greater<edge> > Q;
int main()
{
	scanf("%d%d%d", &n, &m, &x);
	while(m--)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		g[0][u].push_back(make_pair(w, v));
		g[1][v].push_back(make_pair(w, u));
	}
	for(int i = 0; i < 2; ++i)
	{
		memset(dist[i], 0x3f, sizeof dist[i]);
		dist[i][x] = 0;
		Q.push(make_pair(dist[i][x], x));
		while(!Q.empty())
		{
			int u = Q.top().second;
			Q.pop();
			if(vis[i][u])
				continue;
			vis[i][u] = 1;
			for(vector<edge>::iterator it = g[i][u].begin(); it != g[i][u].end(); ++it)
			{
				int &v = it -> second, &w = it -> first;
				if(dist[i][v] > dist[i][u] + w)
				{
					dist[i][v] = dist[i][u] + w;
					Q.push(make_pair(dist[i][v], v));
				}
			}
		}
	}
	for(int i = 1; i <= n; ++i)
		if(ans < dist[0][i] + dist[1][i])
			ans = dist[0][i] + dist[1][i];
	printf("%d\n", ans);
	return 0;
}
