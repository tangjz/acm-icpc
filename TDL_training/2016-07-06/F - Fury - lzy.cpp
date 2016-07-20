#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

constexpr int N = 300;

int n, m, q;
int u, v, f[N + 9];
int t, s[N + 9];
vector<int> lnk[N + 9];
int stp, dfn[N + 9], low[N + 9];
bool ins[N + 9];
bool g[N + 9][N + 9], h[N + 9][N + 9];

void dfs(int u) {
	dfn[u] = low[u] = ++stp;
	ins[u] = true;
	s[t++] = u;

	for (auto v: lnk[u]) {
		if (!dfn[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
		else {
			if (ins[v]) low[u] = min(low[u], dfn[v]);
		}
	}

	if (dfn[u] == low[u]) {
		int v = u;
		do {
			g[v][s[t - 1]] = true;
			v = s[--t];
			f[v] = u;
			ins[v] = false;
		} while (u != v);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	while (m--) {
		scanf("%d%d", &u, &v);
		lnk[u].push_back(v);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i]) dfs(i);
	for (int i = 1; i <= n; ++i)
		for (auto v: lnk[i])
			g[f[i]][f[v]] = true;
	for (int i = 1; i <= n; ++i) g[i][i] = false;

	for (int i = 1; i <= n; ++i) if (f[i] == i)
			for (int j = 1; j <= n; ++j) if (f[j] == j)
				h[i][j] = g[i][j];



	for (int k = 1; k <= n; ++k) if (f[k] == k)
		for (int i = 1; i <= n; ++i)  if (f[i] == i)
			for (int j = 1; j <= n; ++j)  if (f[j] == j)
				h[i][j] |= h[i][k] && h[k][j];


	for (int i = 1; i <= n; ++i) h[i][i] = false;

	//~ for (int i = 1; i <= n; ++i)
		//~ for (int j = 1; j <= n; ++j)
			//~ if (h[i][j])
				//~ printf("h: %d %d\n", i, j);

	m = 0;
	for (int i = 1; i <= n; ++i) if (f[i] == i)
		for (int j = 1; j <= n; ++j) if (f[j] == j)
			if (g[i][j]) {
				for (int k = 1; k <= n; ++k) if (f[k] == k)
					if (h[i][k] && h[k][j]) {
						g[i][j] = false;
						break;
					}
			}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			m += g[i][j];

	printf("%d %d\n", n, m);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (g[i][j])
				printf("%d %d\n", i, j);

	return 0;
}
