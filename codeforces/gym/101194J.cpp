#include <bits/stdc++.h>
using namespace std;
const int maxn = 1803, maxm = 4501, INF = 0x3f3f3f3f;
int N, M, S, T, flow, cost, lnk[maxn], d[maxn], p[maxn], a[maxn]; bool inq[maxn];
struct Edge { int nxt, v, w, c; } e[maxm << 1 | 1];
void addEdge(int u, int v, int w, int c) {
	e[M] = (Edge){lnk[u],v,w, c},lnk[u] = M++;
	e[M] = (Edge){lnk[v],u,0,-c},lnk[v] = M++;
}
bool BellmanFord() {
	memset(d, 0x3f, N * sizeof(int));
	memset(inq, 0, N * sizeof(bool));
	d[S] = 0; inq[S] = 1; p[S] = 0; a[S] = INF;
	std::queue<int> Q; Q.push(S);
	while(!Q.empty()) {
		int u = Q.front(); Q.pop(); inq[u] = 0;
		for(int it = lnk[u];~it;it = e[it].nxt) {
			int v = e[it].v;
			if(e[it].w&&d[v] > d[u] + e[it].c) {
				d[v] = d[u] + e[it].c; p[v] = it;
				a[v] = std::min(a[u], e[it].w);
				if(!inq[v])Q.push(v),inq[v] = 1;
			}
		}
	}
	if(d[T] == INF) return 0;
	flow += a[T]; cost += d[T] * a[T];
	for(int u = T; u != S; u = e[p[u] ^ 1].v)
		e[p[u]].w -= a[T],
		e[p[u] ^ 1].w += a[T];
	return 1;
}
int main() {
	int t, n, m, q;
	bool sp[maxn];
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d", &n, &m);
		N = n * m * 2 + 2, S = N - 2, T = N - 1;
		M = flow = cost = 0;
		memset(lnk, -1, N * sizeof(int));
		for(int i = 0; i < n; ++i)
			for(int j = 0; j + 1 < m; ++j) {
				int u = i * m + j, v = u + 1, w;
				scanf("%d", &w);
				if((i & 1) != (j & 1))
					swap(u, v);
				addEdge(u << 1 | 0, v << 1 | 1, 1, -w);
			}
		for(int i = 0; i + 1 < n; ++i)
			for(int j = 0; j < m; ++j) {
				int u = i * m + j, v = u + m, w;
				scanf("%d", &w);
				if((i & 1) == (j & 1))
					swap(u, v);
				addEdge(u << 1 | 0, v << 1 | 1, 1, -w);
			}
		scanf("%d", &q);
		memset(sp, 0, n * m * sizeof(bool));
		while(q--) {
			int x, y;
			scanf("%d%d", &x, &y);
			sp[(--x) * m + (--y)] = 1;
		}
		for(int i = 0; i < n * m; ++i) {
			addEdge(S, i << 1 | 0, 1, 0);
			addEdge(i << 1 | 1, T, 1, 0);
			if(!sp[i])
				addEdge(i << 1 | 0, i << 1 | 1, 1, 0);
		}
		while(BellmanFord());
		if(flow < n * m) {
			printf("Case #%d: Impossible\n", Case);
		} else {
			printf("Case #%d: %d\n", Case, -cost);
		}
	}
	return 0;
}
