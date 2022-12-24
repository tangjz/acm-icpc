#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, a[maxn], b[maxn], c[maxn];
int tot, stk[maxn], ord[maxn];
inline int cross2(int u, int v) {
	return a[u] * b[v] - b[u] * a[v];
}
inline int cross3(int u, int v, int w) {
	return cross2(u, v) * c[w] + cross2(v, w) * c[u] + cross2(w, u) * c[v];
}
inline bool cmp(int const &u, int const &v) {
	return cross2(u, v) > 0;
}
int main() {
	scanf("%d", &n);
	scanf("%d%d", a + n, b + n);
	for(int i = 0; i < n; ++i) {
		scanf("%d%d%d", a + i, b + i, c + i);
		ord[i] = i;
	}
	sort(ord, ord + n, cmp);
	for(int i = 0; i < n; ++i) {
		int o = ord[i];
		for( ; tot > 1 && cross3(stk[tot - 2], stk[tot - 1], o) >= 0; --tot);
		if(!tot || cross2(stk[tot - 1], o)) {
			stk[tot++] = o;
		} else {
			int p = stk[tot - 1];
			if(c[o] * a[p] - a[o] * c[p] > 0)
				stk[tot - 1] = o;
		}
	}
	for( ; tot > 1 && a[stk[tot - 2]] * c[stk[tot - 1]] - a[stk[tot - 1]] * c[stk[tot - 2]] < 0; --tot);
	int sta = 0;
	for( ; sta + 1 < tot && b[stk[sta + 1]] * c[stk[sta]] - b[stk[sta]] * c[stk[sta + 1]] < 0; ++sta);
	double ans = min(b[n] * c[stk[sta]] / (double)b[stk[sta]], a[n] * c[stk[tot - 1]] / (double)a[stk[tot - 1]]);
	for(int i = sta, j = i + 1; j < tot; i = j, ++j)
		ans = min(ans, ((long long)a[n] * (b[stk[j]] * c[stk[i]] - b[stk[i]] * c[stk[j]]) + (long long)b[n] * (a[stk[i]] * c[stk[j]] - a[stk[j]] * c[stk[i]])) / (double)cross2(stk[i], stk[j]));
	printf("%.3f\n", ans);
	return 0;
}