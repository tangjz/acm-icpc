#include <cmath>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef long double DB;
const int maxn = 201, maxm = maxn * maxn, maxs = 13;
const DB eps = 1e-8, INF = 1e4;
inline int sgn(DB x) {
	assert(!std::isnan(x));
	return (x > eps) - (x < -eps);
}
inline DB readDB() {
	static char buf[maxs];
	scanf("%s", buf);
	LL ret = 0, base = 1;
	char *pat = buf;
	for( ; *pat && *pat != '.'; ++pat)
		ret = (ret << 3) + (ret << 1) + (*pat - '0');
	if(*pat == '.')
		for(++pat; *pat; ++pat) {
			ret = (ret << 3) + (ret << 1) + (*pat - '0');
			base = (base << 3) + (base << 1);
		}
	for( ; !(ret & 1) && !(base & 1); ret >>= 1, base >>= 1);
	for( ; !(ret % 5) && !(base % 5); ret /= 5, base /= 5);
	return (DB)ret / base;
}
inline void writeDB(DB x, char endc = '\0') {
	printf("%.20f", (double)x);
	endc && putchar(endc);
}
int N, M, S, T, lev[maxn], lnk[maxn], cur[maxn];
struct Edge {
	int nxt, v;
	DB w;
} e[maxm << 2 | 1];
void addEdge(int u, int v, DB w) {
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
	while(L < R)
		for(int u = que[L++], it = lnk[u]; it != -1; it = e[it].nxt)
			if(sgn(e[it].w) > 0 && lev[e[it].v] == -1) {
				lev[e[it].v] = lev[u] + 1;
				que[R++] = e[it].v;
			}
	return lev[T] != -1;
}
DB dfs(int u, DB upp) {
	if(u == T)
		return upp;
	DB ret = 0, tmp;
	for(int &it = cur[u]; ~it; it = e[it].nxt)
		if(lev[e[it].v] == lev[u] + 1 && sgn(e[it].w) > 0
		&& sgn(tmp = dfs(e[it].v, min(upp - ret, e[it].w))) > 0) {
			e[it].w -= tmp;
			e[it ^ 1].w += tmp;
			if(sgn((ret += tmp) - upp) >= 0)
				break;
		}
	if(!sgn(ret))
		lev[u] = -1;
	return ret;
}
DB dinic(int s, int t, DB lim = INF) {
	DB flow = 0, tmp;
	for(S = s, T = t; bfs() && sgn(lim - flow) > 0; )
		for(memcpy(cur, lnk, N * sizeof(int)); sgn(lim - flow) > 0 && sgn(tmp = dfs(S, lim - flow)) > 0; flow += tmp);
	return flow;
}
int n, m;
DB v, a, fmx, wmx, zmx, cap[2][maxm], ans;
int main() {
	scanf("%d%d", &n, &m);
	v = readDB();
	a = readDB();
	N = n;
	M = 0;
	memset(lnk, -1, N * sizeof(int));
	for(int i = 0; i < m; ++i) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		--u;
		--v;
		addEdge(u, v, w);
		addEdge(v, u, w);
	} // M = 4 m
	fmx = dinic(0, 2);
	zmx = fmx + dinic(1, 2);
	for(int i = 0; i < M; i += 2) {
		if((i >> 1) & 1)
			cap[0][i >> 2] -= e[i ^ 1].w;
		else
			cap[0][i >> 2] += e[i ^ 1].w;
		e[i].w += e[i ^ 1].w;
		e[i ^ 1].w = 0;
	}
	wmx = dinic(1, 2, zmx);
	dinic(0, 2, zmx - wmx);
	for(int i = 0; i < M; i += 2) {
		if((i >> 1) & 1)
			cap[1][i >> 2] -= e[i ^ 1].w;
		else
			cap[1][i >> 2] += e[i ^ 1].w;
		e[i].w += e[i ^ 1].w;
		e[i ^ 1].w = 0;
	}
	ans = min(max((1 - a) * zmx, zmx - fmx), wmx);
	DB dt = sgn(fmx + wmx - zmx) > 0 ? (wmx - ans) / (fmx + wmx - zmx) : 0;
	for(int i = 0; i < m; ++i) {
		DB cc = dt * cap[0][i] + (1 - dt) * cap[1][i];
		e[i << 2].w = sgn(cc) > 0 ? cc : 0;
		e[i << 2 | 2].w = sgn(cc) < 0 ? -cc : 0;
	}
	dinic(1, 2, ans);
	for(int i = 0; i < m; ++i) {
		DB cc = dt * cap[0][i] + (1 - dt) * cap[1][i], ww = e[i << 2 | 1].w - e[i << 2 | 3].w;
		writeDB((cc - ww) / v, ' ');
		writeDB(ww, '\n');
	}
	writeDB(pow((zmx - ans) / v, a) * pow(ans, 1 - a), '\n');
	return 0;
}
