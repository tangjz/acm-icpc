#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxn = (int)1e5 + 1;
const double INF = 1e20;
int n, m, a[maxn << 1 | 1], b[maxn << 1 | 1], c[maxn];
int tot, stk[maxn], ord[maxn << 1 | 1];
double ans[maxn];
inline LL cross2(int u, int v) {
	return (LL)a[u] * b[v] - (LL)b[u] * a[v];
}
inline LL cross3(int u, int v, int w) {
	return cross2(u, v) * c[w] + cross2(v, w) * c[u] + cross2(w, u) * c[v];
}
inline bool cmp(int const &u, int const &v) {
	return cross2(u, v) > 0;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n + m; ++i) {
		scanf("%d%d", a + i, b + i);
		if(i < n)
			scanf("%d", c + i);
		ord[i] = i;
	}
	std::sort(ord, ord + n + m, cmp);
	for(int i = 0; i < n + m; ++i) {
		int o = ord[i];
		if(o >= n)
			continue;
		for( ; tot > 1 && cross3(stk[tot - 2], stk[tot - 1], o) >= 0; --tot);
		if(!tot || cross2(stk[tot - 1], o)) {
			stk[tot++] = o;
		} else {
			int p = stk[tot - 1];
			if((LL)c[o] * a[p] - (LL)a[o] * c[p] > 0)
				stk[tot - 1] = o;
		}
	}
	for(int i = 0, j = 0; i < n + m; ++i) {
		int o = ord[i];
		if(o < n)
			continue;
		for( ; j < tot && cross2(stk[j], o) > 0; ++j);
		if(j < tot && !cross2(stk[j], o)) {
			int p = stk[j];
			ans[o - n] = (LL)a[o] * c[p] / (double)a[p];
		} else if(!j || j == tot) {
			ans[o - n] = -INF * 2;
		} else {
			int u = stk[j - 1], v = stk[j], w = o;
			ans[o - n] = -(cross2(v, w) * c[u] + cross2(w, u) * c[v]) / (double)cross2(u, v);
		}
	}
	for(int i = 0; i < m; ++i)
		if(ans[i] < -INF) {
			puts("IMPOSSIBLE");
		} else {
			printf("%.5f\n", ans[i]);
		}
	return 0;
}