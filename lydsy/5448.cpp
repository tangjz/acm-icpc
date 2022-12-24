#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 503, maxm = 10001, INF = 0x3f3f3f3f;
int N, M, S, T, lev[maxn], lnk[maxn], cur[maxn];
struct Edge {
	int nxt, v, w;
} e[maxm << 1 | 1];
void addEdge(int u, int v, int w) {
	e[M] = (Edge){lnk[u], v, w};
	lnk[u] = M++;
	e[M] = (Edge){lnk[v], u, 0};
	lnk[v] = M++;
}
bool bfs() {
	int L = 0, R = 0;
	static int que[maxn];
	memset(lev, -1, N * sizeof(int));
	lev[S] = 0;
	que[R++] = S;
	while(L < R) {
		int u = que[L++];
		for(int it = lnk[u]; it != -1; it = e[it].nxt)
			if(e[it].w > 0 && lev[e[it].v] == -1) {
				lev[e[it].v] = lev[u] + 1;
				que[R++] = e[it].v;
			}
	}
	return lev[T] != -1;
}
int dfs(int u, int upp) {
	if(u == T)
		return upp;
	int ret = 0, tmp;
	for(int &it = cur[u]; it != -1; it = e[it].nxt)
		if(lev[e[it].v] == lev[u] + 1 && e[it].w > 0
		&& (tmp = dfs(e[it].v, std::min(upp - ret, e[it].w))) > 0) {
			e[it].w -= tmp;
			e[it ^ 1].w += tmp;
			if((ret += tmp) == upp)
				break;
		}
	if(!ret)
		lev[u] = -1;
	return ret;
}
int t, n, w, m1, m2, coeff[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d%d", &n, &w, &m1, &m2);
		N = n + 2;
		M = 0;
		S = 0;
		T = n + 1;
		memset(lnk, -1, N * sizeof(int));
		memset(coeff + 1, 0, n * sizeof(int));
		int flow = 0;
		while(m1--) {
			int x, y, z, a, b, c, d, e, f;
			scanf("%d%d%d%d%d%d%d%d%d", &x, &y, &z, &a, &b, &c, &d, &e, &f);
			addEdge(x, y, a << 1);
			addEdge(y, x, a << 1);
			addEdge(y, z, b << 1);
			addEdge(z, y, b << 1);
			addEdge(z, x, c << 1);
			addEdge(x, z, c << 1);
			coeff[x] += d - f;
			coeff[y] += e - d;
			coeff[z] += f - e;
		}
		while(m2--) {
			int x, y, r;
			scanf("%d%d%d", &x, &y, &r);
			switch(r) {
				case 0 : {
					addEdge(y, x, INF);
					break;
				}
				case 1 : {
					addEdge(x, y, INF);
					addEdge(y, x, INF);
					break;
				}
				case 2 : {
					addEdge(S, x, INF);
					addEdge(y, T, INF);
					break;
				}
			}
		}
		for(int i = 1; i <= n; ++i)
			flow = std::max(flow, std::abs(++coeff[i]));
		for(int i = 1; i <= n; ++i) {
			addEdge(S, i, flow + coeff[i]);
			addEdge(i, T, flow - coeff[i]);
		}
		flow = -flow * n;
		while(bfs()) {
			memcpy(cur, lnk, N * sizeof(int));
			for(int tmp; (tmp = dfs(S, INF)); flow += tmp);
		}
		printf("%lld\n", (LL)flow * w);
	}
	return 0;
}
