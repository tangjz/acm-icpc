#include <bits/stdc++.h>
const int maxn = (int)1e3 + 1, maxm = (int)1e4 + 1;
int n, a[maxn], b[maxn], c[maxn], ord[maxn], m, o, f[2][maxm];
char buf[maxm];
bool cmp(int const &u, int const &v) {
	bool su = a[u] < b[u], sv = a[v] < b[v];
	if(su != sv)
		return su > sv;
	return su ? (a[u] < a[v]) : (b[u] > b[v]);
}
inline void upd(int &x, int y, int z) {
	y != -1 && (y += z) && x < y && (x = y);
}
int main() {
	while(scanf("%d", &n) == 1) {
		for(int i = 0; i < n; ++i) {
			scanf("%s", buf);
			a[i] = b[i] = 0;
			c[i] = strlen(buf);
			for(int j = 0; buf[j]; ++j)
				if(buf[j] == '(') {
					++b[i];
				} else if(b[i]) {
					--b[i];
				} else {
					++a[i];
				}
			ord[i] = i;
		}
		std::sort(ord, ord + n, cmp);
		m = f[o][0] = 0;
		for(int i = 0; i < n; ++i) {
			int u = ord[i];
			o = !o;
			memcpy(f[o], f[!o], (m + 1) * sizeof(int));
			if(m < a[u])
				continue;
			int dt = b[u] - a[u], upp = m;
			if(dt > 0) {
				upp += dt;
				memset(f[o] + (m + 1), -1, dt * sizeof(int));
			}
			for(int j = a[u]; j <= m; ++j)
				upd(f[o][j + dt], f[!o][j], c[u]);
			m = upp;
		}
		printf("%d\n", f[o][0]);
	}
	return 0;
}