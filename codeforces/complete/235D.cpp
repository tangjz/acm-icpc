#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)3e3 + 1;
int n, m, seq[maxn], idx[maxn], dep[maxn];
vector<int> e[maxn];
bool vis[maxn], ban[maxn];
bool pfs(int u) {
	vis[u] = 1;
	seq[m++] = u;
	for(auto &v : e[u])
		if(vis[v]) {
			if(m > 1 && v == seq[m - 2])
				continue;
			for(int i = m - 3; i >= 0; --i)
				if(v == seq[i]) {
					rotate(seq, seq + i, seq + m);
					m -= i;
					break;
				}
			return 1;
		} else if(pfs(v)) {
			return 1;
		}
	--m;
	vis[u] = 0;
	return 0;
}
int f[maxn][maxn], g[maxn][maxn], h[maxn];
int dfs(int u, int fa) {
	int su = 1;
	f[u][0] = 1;
	g[u][0] = 1;
	for(auto &v : e[u]) {
		if(v == fa || ban[v])
			continue;
		idx[v] = idx[u];
		dep[v] = dep[u] + 1;
		int sv = dfs(v, u);
		memset(f[u] + su, 0, sv * sizeof(int));
		memset(g[u] + su, 0, sv * sizeof(int));
		for(int i = 0; i < su; ++i) if(f[u][i])
			for(int j = 0; j < sv; ++j) if(f[v][j])
				g[u][i + j + 1] += 2 * f[u][i] * f[v][j];
		for(int i = 0; i < sv; ++i) {
			f[u][i + 1] += f[v][i];
			g[u][i] += g[v][i];
		}
		su += sv;
	}
	return su;
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	pfs(1);
	memset(vis, 0, n * sizeof(bool));
	for(int i = 0; i < m; ++i)
		ban[seq[i]] = 1;
	for(int i = 0; i < m; ++i) {
		idx[seq[i]] = i;
		dep[seq[i]] = 0;
		int si = dfs(seq[i], -1);
		for(int j = 0; j < si; ++j)
			h[j + 1] += g[seq[i]][j];
	}
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			if(idx[i] != idx[j]) {
				int u = abs(idx[i] - idx[j]), v = m - u, w = dep[i] + dep[j];
				++h[u + w + 1];
				++h[v + w + 1];
				--h[u + v + w];
			}
	double ans = 0;
	for(int i = 1; i <= n; ++i)
		ans += (double)h[i] / i;
	printf("%.20f\n", ans);
	return 0;
}
