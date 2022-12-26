#include <bits/stdc++.h>
using namespace std;
const int maxn = 403, maxm = 2001, INF = 0x3f3f3f3f;
int N, M, S, T, lnk[maxn], dis[maxn], sum, flow, cost;
struct Edge {
	int nxt, v, w, c;
} e[maxm << 1 | 1];
bool vis[maxn];
void addEdge(int u, int v, int w, int c) {
	e[M] = (Edge){lnk[u], v, w, c};
	lnk[u] = M++;
	e[M] = (Edge){lnk[v], u, 0, -c};
	lnk[v] = M++;
}
bool Dijkstra() {
	priority_queue<pair<int, int> > Q;
	memset(dis, 0x3f, N * sizeof(int));
	memset(vis, 0, N * sizeof(bool));
	dis[T] = 0;
	for( ; !Q.empty(); Q.pop());
	Q.push(make_pair(-dis[T], T));
	while(!Q.empty()) {
		int u = Q.top().second;
		Q.pop();
		if(vis[u])
			continue;
		vis[u] = 1;
		for(int it = lnk[u]; it != -1; it = e[it].nxt) {
			if(!e[it ^ 1].w)
				continue;
			int v = e[it].v, tp = dis[u] + e[it ^ 1].c;
			if(tp < dis[v]) {
				dis[v] = tp;
				Q.push(make_pair(-dis[v], v));
			}
		}
	}
	if(dis[S] == INF)
		return 0;
	for(int u = 0; u < N; ++u)
		for(int it = lnk[u]; it != -1; it = e[it].nxt)
			e[it].c += dis[e[it].v] - dis[u];
	sum += dis[S];
	return 1;
}
int dfs(int u, int upp) {
	if(u == T)
		return upp;
	vis[u] = 1;
	int ret = 0, tmp;
	for(int it = lnk[u]; it != -1; it = e[it].nxt)
		if(!e[it].c && !vis[e[it].v] && e[it].w
		&& (tmp = dfs(e[it].v, min(upp - ret, e[it].w))) > 0) {
			e[it].w -= tmp;
			e[it ^ 1].w += tmp;
			if((ret += tmp) == upp)
				break;
		}
	return ret;
}
void MinCostMaxFlow(int upp = INF) {
	Dijkstra();
	do while(upp > 0) {
		memset(vis, 0, N * sizeof(bool));
		int adt = dfs(S, upp);
		if(!adt)
			break;
		upp -= adt;
		flow += adt;
		cost += adt * sum;
	} while(Dijkstra());
}
int main() {
	int t, n, m, x, y, upp;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &x);
		N = n + n + 2;
		S = N - 2;
		T = N - 1;
		M = sum = flow = cost = upp = 0;
		memset(lnk, -1, N * sizeof(int));
		addEdge(S, 0, x, 0);
		for(int i = 0; i < n; ++i) {
			scanf("%d", &x);
			upp += x;
			if(i > 0)
				addEdge(i - 1, i, INF, 0);
			addEdge(i, T, x, 0);
			addEdge(S, n + i, x, 0);
		}
		scanf("%d%d%d", &m, &x, &y);
		addEdge(S, x - 1, INF, y);
		while(m--) {
			scanf("%d%d", &x, &y);
			for(int i = y; i < n; ++i)
				addEdge(n + i - y, i, INF, x);
		}
		MinCostMaxFlow(upp);
		if(flow < upp) {
			puts("No solution");
		} else {
			printf("%d\n", cost);
		}
	}
	return 0;
}
