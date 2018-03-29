#include <bits/stdc++.h>
using namespace std;
const int maxn = 5001, maxm = maxn << 1 | 1;
int n, m, dsu[maxm], cB[maxm], cW[maxm], cE[maxm];
char buf[maxn];
int dsu_find(int u) {
	return dsu[u] < 0 ? u : (dsu[u] = dsu_find(dsu[u]));
}
void dsu_merge(int u, int v) {
	u = dsu_find(u);
	v = dsu_find(v);
	if(u == v) {
		++cE[u];
		return;
	}
	if(dsu[u] < dsu[v])
		swap(u, v);
	dsu[v] -= dsu[u] == dsu[v];
	dsu[u] = v;
	cB[v] += cB[u];
	cW[v] += cW[u];
	cE[v] += cE[u] + 1;
}
int main() {
	scanf("%d%d", &n, &m);
	memset(dsu, -1, (n + m) * sizeof(int));
	for(int i = 0; i < n; ++i)
		cB[i] = 1;
	for(int i = 0; i < m; ++i)
		cW[n + i] = 1;
	for(int i = 0; i < n; ++i) {
		scanf("%s", buf);
		for(int j = 0; j < m; ++j)
			if(buf[j] != '.')
				dsu_merge(i, n + j);
	}
	for(int i = 0; i < n + m; ++i)
		if(dsu_find(i) == i && cB[i] * cW[i] != cE[i]) {
			puts("No");
			return 0;
		}
	puts("Yes");
	return 0;
}
