#include <queue>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef pair<LL, int> Edge;
const int maxn = 300001, INF = 0x3f3f3f3f;
int n, m, S;
LL dis[maxn], pre[maxn], ans;
vector<Edge> e[maxn];
priority_queue<Edge, vector<Edge>, greater<Edge> > Q;
bool vis[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	while(m--)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		e[u].push_back(make_pair(w, v));
		e[v].push_back(make_pair(w, u));
	}
	scanf("%d", &S);
	memset(dis + 1, 0x3f, n * sizeof(LL));
	memset(vis + 1, 0, n * sizeof(bool));
	dis[S] = 0;
	Q.push(make_pair(dis[S], S));
	while(!Q.empty())
	{
		int u = Q.top().second;
		Q.pop();
		if(vis[u])
			continue;
		vis[u] = 1;
		for(vector<Edge>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		{
			int v = it -> second;
			LL w = dis[u] + (it -> first);
			if(w < dis[v])
			{
				dis[v] = w;
				pre[v] = it -> first;
				Q.push(make_pair(dis[v], v));
			}
			else if(w == dis[v] && (it -> first) < pre[v])
				pre[v] = it -> first;
		}
	}
	for(int i = 1; i <= n; ++i)
		ans += pre[i];
	printf("%lld\n", ans);
	return 0;
}
