#include <queue>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef pair<int, int> Edge;
const int maxn = 50, maxd = 20000, maxs = maxn * maxd, INF = 0x3f3f3f3f;
int t, n, m, cir, dis[maxs];
LL dist;
vector<Edge> e[maxn];
priority_queue<Edge, vector<Edge>, greater<Edge> > Q;
bool vis[maxs];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%lld", &n, &m, &dist);
		for(int i = 0; i < n; ++i)
			vector<Edge>().swap(e[i]);
		cir = maxd;
		while(m--)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			if((!u || !v) && w < cir)
				cir = w;
			e[u].push_back(make_pair(w, v));
			e[v].push_back(make_pair(w, u));
		}
		if(cir == maxd)
		{
			puts("Impossible");
			continue;
		}
		cir <<= 1;
		memset(dis, 0x3f, n * cir * sizeof(int));
		memset(vis, 0, n * cir * sizeof(bool));
		dis[0] = 0;
		Q.push(make_pair(dis[0], 0));
		while(!Q.empty())
		{
			int udx = Q.top().second;
			Q.pop();
			if(vis[udx])
				continue;
			vis[udx] = 1;
			int u = udx / cir;
			for(vector<Edge>::iterator it = e[u].begin(); it != e[u].end(); ++it)
			{
				int v = it -> second, w = dis[udx] + (it -> first), vdx = v * cir + w % cir;
				if(w < dis[vdx])
				{
					dis[vdx] = w;
					Q.push(make_pair(dis[vdx], vdx));
				}
			}
		}
		int udx = (n - 1) * cir + dist % cir;
		puts(dis[udx] != INF && dis[udx] <= dist ? "Possible" : "Impossible");
	}
	return 0;
}
