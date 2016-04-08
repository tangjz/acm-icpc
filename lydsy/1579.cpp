#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 210001, maxm = 1050001;
int n, m, t, tot, pre[maxn];
long long dis[maxn], ans;
bool vis[maxn];
struct Edge
{
	int nxt, v, w;
} e[maxm << 2];
priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > Q;
void AddEdge(int u, int v, int w)
{
	e[++tot] = (Edge){pre[u], v, w};
	pre[u] = tot;
}
int main()
{
	scanf("%d%d%d", &n, &m, &t);
	while(m--)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		--u, --v;
		for(int i = 0; i <= t; ++i)
		{
			AddEdge(i * n + u, i * n + v, w);
			AddEdge(i * n + v, i * n + u, w);
			if(i < t)
			{
				AddEdge(i * n + u, (i + 1) * n + v, 0);
				AddEdge(i * n + v, (i + 1) * n + u, 0);
			}
		}
	}
	memset(dis, 0x3f, sizeof dis);
	dis[0] = 0;
	Q.push(make_pair(dis[0], 0));
	while(!Q.empty())
	{
		int u = Q.top().second;
		Q.pop();
		if(vis[u])
			continue;
		vis[u] = 1;
		for(int it = pre[u]; it; it = e[it].nxt)
		{
			int &v = e[it].v, &w = e[it].w;
			if(dis[v] > dis[u] + w)
			{
				dis[v] = dis[u] + w;
				Q.push(make_pair(dis[v], v));
			}
		}
	}
	ans = 0x3f3f3f3f3f3f3f3fLL;
	for(int i = 0; i <= t; ++i)
		if(ans > dis[i * n + n - 1])
			ans = dis[i * n + n - 1];
	printf("%lld\n", ans);
	return 0;
}
