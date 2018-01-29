#include <bits/stdc++.h>
using namespace std;
const int maxn = 23, maxs = 1 << 22 | 1;
int n, m, all, e[maxn], g[maxn], dsu[maxn][maxn], ans, out;
int dsu_find(int dsu[], int x) {
	return dsu[x] < 0 ? x : dsu[x] = dsu_find(dsu, dsu[x]);
}
void dsu_merge(int dsu[], int u, int v) {
	u = dsu_find(dsu, u);
	v = dsu_find(dsu, v);
	if(u == v)
		return;
	if(dsu[u] < dsu[v])
		swap(u, v);
	if(dsu[u] == dsu[v])
		--dsu[v];
	dsu[u] = v;
}
void dfs(int dep, int sel, int cov) {
	if(dep == n) {
		if(cov < all)
			return;
		int cnt = 0;
		for(int i = 0, fir = -1; i < n; ++i) {
			if(!(sel & (1 << i)))
				continue;
			++cnt;
			if(fir == -1)
				fir = i;
			else if(dsu_find(dsu[n], fir) != dsu_find(dsu[n], i))
				return;
		}
		if(cnt < ans) {
			ans = cnt;
			out = sel;
		}
		return;
	}
	memcpy(dsu[dep + 1], dsu[dep], n * sizeof(int));
	dfs(dep + 1, sel, cov);
	int adt = e[dep] & sel;
	for(int i = 0; i < n; ++i)
		if(adt & (1 << i))
			dsu_merge(dsu[dep + 1], dep, i);
	dfs(dep + 1, sel | 1 << dep, cov | e[dep]);
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		e[i] |= 1 << i;
	for(int i = 0; i < m; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		--u, --v;
		e[u] |= 1 << v;
		e[v] |= 1 << u;
	}
	if(m == n * (n - 1) / 2) {
		puts("0");
		return 0;
	}
	ans = n;
	out = all = (1 << n) - 1;
	memset(dsu[0], -1, n * sizeof(int));
	dfs(0, 0, 0);
	printf("%d\n", ans);
	for(int i = 0, fir = 1; i < n; ++i)
		if(out & (1 << i)) {
			if(fir)
				fir = 0;
			else
				putchar(' ');
			printf("%d", i + 1);
		}
	puts("");
	return 0;
}
