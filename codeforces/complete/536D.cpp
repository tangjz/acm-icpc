#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e3 + 1, INF = 0x3f3f3f3f;
const LL INF2 = 0x3f3f3f3f3f3f3f3fLL;
int n, m, S, T, a[maxn], e[maxn][maxn], p[2][maxn], c[maxn][maxn];
LL s[maxn][maxn], f[maxn][maxn], g[maxn][maxn];
pair<LL, int> mf[maxn], mg[maxn];
int getDist(int rt, int rk[]) {
	static LL dis[maxn];
	static bool vis[maxn];
	memset(dis, 0x3f, (n + 1) * sizeof(LL));
	memset(vis + 1, 0, n * sizeof(bool));
	dis[rt] = rk[rt] = 0;
	int las = rt;
	for(int i = 1; i <= n; ++i) {
		int u = 0;
		for(int v = 1; v <= n; ++v)
			if(!vis[v] && dis[v] < dis[u])
				u = v;
		vis[u] = 1;
		for(int v = 1; v <= n; ++v)
			if(e[u][v] < INF)
				dis[v] = min(dis[v], dis[u] + e[u][v]);
		rk[u] = rk[las] + (dis[las] < dis[u]);
		las = u;
	}
	return rk[las] + 1;
}
int main() {
	scanf("%d%d%d%d", &n, &m, &S, &T);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		memset(e[i] + 1, 0x3f, n * sizeof(int));
		e[i][i] = 0;
	}
	while(m--) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		if(e[u][v] > w)
			e[u][v] = e[v][u] = w;
	}
	S = getDist(S, p[0]);
	T = getDist(T, p[1]);
	for(int i = 1; i <= n; ++i) {
		int x = p[0][i], y = p[1][i];
		++c[x][y];
		s[x][y] += a[i];
	}
	for(int i = 0; i < S; ++i)
		mf[i] = make_pair(INF2, T);
	for(int i = 0; i < T; ++i)
		mg[i] = make_pair(INF2, S);
	for(int i = S - 1; i >= 0; --i)
		for(int j = T - 1; j >= 0; --j) {
			c[i][j] = c[i][j] + c[i + 1][j] + c[i][j + 1] - c[i + 1][j + 1];
			s[i][j] = s[i][j] + s[i + 1][j] + s[i][j + 1] - s[i + 1][j + 1];
			if(!c[i][j])
				continue;
			for( ; c[mg[j].second][j] < c[i][j]; --mg[j].second)
				mg[j].first = min(mg[j].first, g[mg[j].second][j]);
			f[i][j] = s[i][j] - mg[j].first;
			for( ; c[i][mf[i].second] < c[i][j]; --mf[i].second)
				mf[i].first = min(mf[i].first, f[i][mf[i].second]);
			g[i][j] = s[i][j] - mf[i].first;
		}
	LL fir = f[0][0], sec = s[0][0] - f[0][0];
	puts(fir > sec ? "Break a heart" : (fir < sec ? "Cry" : "Flowers"));
	return 0;
}