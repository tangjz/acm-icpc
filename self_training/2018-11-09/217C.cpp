#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e3 + 1, INF = 0x3f3f3f3f;
int n, m, a[maxn], ord[maxn], tot, que[maxn], fa[maxn], f[maxn][maxn];
vector<int> e[maxn];
bool check(int lim) {
	for(int i = n; i >= 1; --i) {
		int u = ord[i];
		for(int j = 1; j <= tot; ++j)
			f[u][j] = que[j] <= a[u] && a[u] <= que[j] + lim ? 0 : INF;
		for(int v : e[u]) {
			if(v == fa[u])
				continue;
			int low = f[v][1];
			for(int j = 2; j <= tot; ++j)
				low = min(low, f[v][j]);
			for(int j = 1; j <= tot; ++j) {
				if(f[u][j] == INF)
					continue;
				f[u][j] += min(f[v][j], low + 1);
			}
		}
	}
	for(int i = 1; i <= tot; ++i)
		if(f[1][i] <= m)
			return 1;
	return 0;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		que[i] = a[i];
	}
	sort(que + 1, que + n + 1);
	tot = unique(que + 1, que + n + 1) - que - 1;
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	ord[1] = 1;
	for(int i = 1, tot = 1; i <= tot; ++i) {
		int u = ord[i];
		for(int v : e[u]) {
			if(v == fa[u])
				continue;
			fa[v] = u;
			ord[++tot] = v;
		}
	}
	int L = 0, R = (int)2e9;
	while(L < R) {
		int M = L + ((R - L) >> 1);
		if(check(M)) {
			R = M;
		} else {
			L = M + 1;
		}
	}
	printf("%d\n", L);
	return 0;
}