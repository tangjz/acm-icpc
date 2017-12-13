#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 30003, maxm = 140001, INF = 0x3f3f3f3f, d[5][2] = {{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int N, M, S, T, lnk[maxn], lev[maxn], cur[maxn], ans;
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
			if(lev[e[it].v] == -1 && e[it].w > 0) {
				lev[e[it].v] = lev[u] + 1;
				que[R++] = e[it].v;
			}
	}
	return lev[T] != -1;
}
int dfs(int u, int lim) {
	if(u == T)
		return lim;
	int ret = 0, tmp;
	for(int &it = cur[u]; it != -1; it = e[it].nxt)
		if(lev[u] + 1 == lev[e[it].v] && e[it].w > 0
		&& (tmp = dfs(e[it].v, min(e[it].w, lim - ret))) > 0) {
			e[it].w -= tmp;
			e[it ^ 1].w += tmp;
			if((ret += tmp) == lim)
				break;
		}
	if(!ret)
		lev[u] = -1;
	return ret;
}
int main() {
	int n, m, all, w;
	scanf("%d%d", &n, &m);
	all = n * m;
	N = all * 3 + 2;
	M = 0;
	S = N - 2;
	T = N - 1;
	memset(lnk, -1, N * sizeof(int));
	for(int i = 0, idx = 0; i < n; ++i)
		for(int j = 0; j < m; ++j, ++idx) {
			scanf("%d", &w);
			ans += w;
			addEdge(S, idx, w);
		}
	for(int i = 0, idx = 0; i < n; ++i)
		for(int j = 0; j < m; ++j, ++idx) {
			scanf("%d", &w);
			ans += w;
			addEdge(idx, T, w);
		}
	for(int i = 0, idx = 0; i < n; ++i)
		for(int j = 0; j < m; ++j, ++idx) {
			scanf("%d", &w);
			ans += w;
			addEdge(S, all + idx, w);
			for(int o = 0; o <= 4; ++o) {
				int x = i + d[o][0], y = j + d[o][1];
				if(x >= 0 && x < n && y >= 0 && y < m)
					addEdge(all + idx, x * m + y, INF);
			}
		}
	for(int i = 0, idx = 0; i < n; ++i)
		for(int j = 0; j < m; ++j, ++idx) {
			scanf("%d", &w);
			ans += w;
			addEdge(all + all + idx, T, w);
			for(int o = 0; o <= 4; ++o) {
				int x = i + d[o][0], y = j + d[o][1];
				if(x >= 0 && x < n && y >= 0 && y < m)
					addEdge(x * m + y, all + all + idx, INF);
			}
		}
	while(bfs()) {
		memcpy(cur, lnk, N * sizeof(int));
		for(int tmp; (tmp = dfs(S, INF)) > 0; ans -= tmp);
	}
	printf("%d\n", ans);
	return 0;
}
