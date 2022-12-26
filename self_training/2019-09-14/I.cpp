#include <bits/stdc++.h>
using namespace std;
const int maxn = 5001, maxm = maxn << 1 | 1, INF = 0x3f3f3f3f;
int N, M, S, T, lev[maxn], lnk[maxn], cur[maxn], side[maxn];
struct Edge {int nxt, v, w;} e[maxm<<1|1];
inline int newNode(int belong = -1) {
	lnk[N] = -1;
	side[N] = belong;
	return N++;
}
inline void addEdge(int u, int v, int w) {
	e[M] = (Edge){lnk[u], v, w}, lnk[u] = M++;
	e[M] = (Edge){lnk[v], u, 0}, lnk[v] = M++;
}
bool bfs() {
	int L = 0, R = 0; static int que[maxn];
	memset(lev, -1, N * sizeof(int));
	lev[S] = 0, que[R++] = S;
	while(L < R) {
		int u = que[L++];
		for(int it = lnk[u]; ~it; it = e[it].nxt)
			if(e[it].w > 0 && lev[e[it].v] == -1)
				lev[e[it].v] = lev[u] + 1,
				que[R++] = e[it].v;
	}
	return lev[T] != -1;
}
int dfs(int u, int upp) {
	if(u == T) return upp; // if !upp
	int ret = 0, tmp;
	for(int &it = cur[u]; ~it; it = e[it].nxt)
		if(lev[e[it].v] == lev[u] + 1 && e[it].w > 0
		&& (tmp = dfs(e[it].v, std::min(upp - ret, e[it].w))) > 0) {
			e[it].w -= tmp, e[it ^ 1].w += tmp;
			if((ret += tmp) == upp) break;
		}
	if(!ret) lev[u] = -1;
	return ret;
}
bool vis[maxn], ban[maxn];
void check(int u, int o) {
	vis[u] = 1;
	if(side[u] == o)
		ban[u] = 1;
	for(int it = lnk[u]; ~it; it = e[it].nxt)
		if(e[it ^ o].w && !vis[e[it].v])
			check(e[it].v, o);
}
const int maxl = 11, maxq = 21, maxs = 101;
int r, c, q, que[maxq], ans[maxq], cntX, cntY, idx[maxs][maxs];
char buf[maxl][maxl];
inline bool isValid(int x, int y) {
	return x >= 0 && x < r && y >= 0 && y < c && buf[x][y] != '#';
}
void pfs(int o, int u1, int u2) {
	int x1 = u1 / c, y1 = u1 % c;
	int x2 = u2 / c, y2 = u2 % c;
	idx[u1][u2] = newNode(o);
	if(o == 0) {
		++cntX;
		addEdge(S, idx[u1][u2], 1);
	} else {
		++cntY;
		addEdge(idx[u1][u2], T, 1);
	}
	for(int dx = -1; dx <= 1; ++dx)
		for(int dy = -1; dy <= 1; ++dy) {
			if(abs(dx) + abs(dy) != 1)
				continue;
			if(isValid(x1 + dx, y1 + dy)) {
				int v1 = u1 + dx * c + dy;
				int v2 = u2;
				if(v1 > v2)
					swap(v1, v2);
				if(v1 != v2 && idx[v1][v2] == -1)
					pfs(!o, v1, v2);
				if(v1 != v2 && !o)
					addEdge(idx[u1][u2], idx[v1][v2], 1);
			}
			if(isValid(x2 + dx, y2 + dy)) {
				int v1 = u1;
				int v2 = u2 + dx * c + dy;
				if(v1 > v2)
					swap(v1, v2);
				if(v1 != v2 && idx[v1][v2] == -1)
					pfs(!o, v1, v2);
				if(v1 != v2 && !o)
					addEdge(idx[u1][u2], idx[v1][v2], 1);
			}
		}
}
int main() {
	while(scanf("%d%d%d", &r, &c, &q) == 3) {
		int rc = r * c;
		for(int i = 0; i < rc; ++i)
			memset(idx[i], -1, rc * sizeof(int));
		for(int i = 0; i < r; ++i)
			scanf("%s", buf[i]);
		for(int i = 0; i < q; ++i) {
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			int u1 = (x1 - 1) * c + y1 - 1;
			int u2 = (x2 - 1) * c + y2 - 1;
			if(u1 > u2)
				swap(u1, u2);
			que[i] = u1 * rc + u2;
			ans[i] = -1;
		}
		for(int i = 0; i < q; ++i) {
			if(ans[i] != -1)
				continue;
			int u1 = que[i] / rc, u2 = que[i] % rc;
			int x1 = u1 / c, y1 = u1 % c;
			int x2 = u2 / c, y2 = u2 % c;
			assert(buf[x1][y1] != '#' && buf[x2][y2] != '#');
			N = M = cntX = cntY = 0;
			S = newNode();
			T = newNode();
			pfs(0, u1, u2);
			int flow = 0, tmp;
			while(bfs()) {
				memcpy(cur, lnk, N * sizeof(int));
				while((tmp = dfs(S, INF))) flow += tmp;
			}
			memset(ban, 0, N * sizeof(bool));
			memset(vis, 0, N * sizeof(bool));
			check(S, 0);
			memset(vis, 0, N * sizeof(bool));
			check(T, 1);
			for(int j = i; j < q; ++j) {
				if(ans[j] != -1)
					continue;
				int u1 = que[j] / rc, u2 = que[j] % rc;
				if(idx[u1][u2] == -1)
					continue;
				if(!ban[idx[u1][u2]]) {
					ans[j] = 0;
				} else {
					ans[j] = 1;
				}
			}
		}
		for(int i = 0; i < q; ++i)
			if(!ans[i]) {
				puts("ghh wins.");
			} else {
				puts("gfh wins.");
			}
	}
	return 0;
}