#include <bits/stdc++.h>
const int maxn = 47, maxd = 23, maxs = 1 << 23 | 1, mod = (int)1e9 + 7;
int n, dsu[maxn], m, idx[maxn], bits[maxs], f[maxs], g[maxs], ans;
char buf[maxn][maxn + 2];
int dsu_find(int u) {
	return dsu[u] < 0 ? u : dsu[u] = dsu_find(dsu[u]);
}
void dsu_merge(int u, int v) {
	u = dsu_find(u);
	v = dsu_find(v);
	if(u == v)
		return;
	dsu[u] += dsu[v];
	dsu[v] = u;
}
int main() { 
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%s", buf[i]);
		dsu[i] = -1;
		for(int j = 0; j < i; ++j)
			if(buf[i][j] == 'A')
				dsu_merge(i, j);
	}
	for(int i = 0; i < n; ++i)
		if(dsu_find(i) == i && -dsu[i] > 1)
			idx[i] = 1 << (m++);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < i; ++j)
			if(buf[i][j] == 'X') {
				int u = dsu_find(i), v = dsu_find(j);
				if(u == v) {
					puts("-1");
					return 0;
				}
				if(idx[u] && idx[v])
					f[idx[u] | idx[v]] = 1;
			}
	if(!m) {
		printf("%d\n", n - 1);
		return 0;
	}
	for(int i = 1; i < 1 << m; ++i)
		for(int j = 0; j < m; ++j)
			if(i & (1 << j))
				f[i] |= f[i ^ (1 << j)];
	for(int i = 0; i < 1 << m; ++i) {
		bits[i] = bits[i >> 1] + (i & 1);
		f[i] = !f[i];
		g[i] = 1;
	}
	for(int i = 0; i < m; ++i)
		for(int j = 0; j < 1 << m; ++j)
			if(j & (1 << i))
				f[j] += f[j ^ (1 << i)];
	for(int i = 1; i <= m; ++i) {
		int ways = 0;
		for(int j = 0; j < 1 << m; ++j) {
			g[j] = (long long)g[j] * f[j] % mod;
			if((m - bits[j]) & 1)
				(ways -= g[j]) < 0 && (ways += mod);
			else
				(ways += g[j]) >= mod && (ways -= mod);
		}
		if(ways) {
			printf("%d\n", n - 1 + i);
			break;
		}
	}
	return 0;
}
// answer = n - 1 + (number of components) - (number of components with size 1)
// minimum (number of components with size > 1)
