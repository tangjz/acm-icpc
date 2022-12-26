#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 501, N = 2001, M = 500001;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
namespace MCMF {
	int n, m, s, t, lnk[N], p[N];
	LL flow, cost, d[N], a[N];
	bool inq[N];
	struct Edge {
		int nxt, v;
		LL w, c;
	} e[M << 1 | 1];
	void AddEdge(int u, int v, LL w, LL c) {
		e[m] = (Edge){lnk[u], v, w, c};
		lnk[u] = m++;
		e[m] = (Edge){lnk[v], u, 0LL, -c};
		lnk[v] = m++;
	}
	bool BellmanFord() {
		for(int i = 0; i < n; ++i)
			d[i] = -INF;
		memset(inq, 0, n * sizeof(bool));
		d[s] = 0;
		inq[s] = 1;
		p[s] = -1;
		a[s] = INF;
		std::queue<int> Q;
		Q.push(s);
		while(!Q.empty()) {
			int u = Q.front();
			Q.pop();
			inq[u] = 0;
			for(int it = lnk[u]; it != -1; it = e[it].nxt) {
				int v = e[it].v;
				if(e[it].w > 0 && d[v] < d[u] + e[it].c) {
					d[v] = d[u] + e[it].c;
					p[v] = it;
					a[v] = std::min(a[u], e[it].w);
					if(!inq[v]) {
						Q.push(v);
						inq[v] = 1;
					}
				}
			}
		}
		if(d[t] <= 0)
			return 0;
		flow += a[t];
		cost += d[t] * a[t];
		for(int u = t; u != s; u = e[p[u] ^ 1].v) {
			e[p[u]].w -= a[t];
			e[p[u] ^ 1].w += a[t];
		}
		return 1;
	}
	LL solve(int N, LL cL[], LL cR[], LL dis[][maxn]) {
		n = (N << 1) + 2;
		m = 0;
		memset(lnk, -1, n * sizeof(int));
		s = N << 1;
		t = N << 1 | 1;
		for(int i = 0; i < N; ++i) {
			AddEdge(s, i, cL[i], 0);
			AddEdge(N + i, t, cR[i], 0);
		}
		for(int i = 0; i < N; ++i)
			for(int j = 0; j < N; ++j)
				if(dis[i][j] > 0)
					AddEdge(i, N + j, std::min(cL[i], cR[j]), dis[i][j]);
		flow = cost = 0;
		while(BellmanFord());
		return cost;
	}
}
int n, m;
LL a[maxn], b[maxn], c[maxn], d[maxn], dis[maxn][maxn];
int main() {
	while(scanf("%d%d", &n, &m) == 2) {
		memset(dis, 0x3f, sizeof dis);
		for(int i = 0; i < n; ++i) {
			scanf("%I64d%I64d%I64d%I64d", a + i, b + i, c + i, d + i);
			dis[i][i] = 0;
		}
		while(m--) {
			int u, v;
			LL w;
			scanf("%d%d%I64d", &u, &v, &w);
			--u, --v;
			dis[u][v] = std::min(dis[u][v], w);
			dis[v][u] = std::min(dis[v][u], w);
		}
		for(int k = 0; k < n; ++k)
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < n; ++j)
					dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				dis[i][j] = c[j] - a[i] - dis[i][j];
		printf("%I64d\n", MCMF::solve(n, b, d, dis));
	}
	return 0;
}
