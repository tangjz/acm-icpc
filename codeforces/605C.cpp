#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
int n, a[maxn], b[maxn], ord[maxn];
int tot, stk[maxn];
inline LL cross2(int u, int v) {
	return (LL)a[u] * b[v] - (LL)a[v] * b[u];
}
inline LL cross3(int u, int v, int w) {
	return cross2(u, v) + cross2(v, w) + cross2(w, u);
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i <= n; ++i) {
		scanf("%d%d", a + i, b + i);
		ord[i] = i;
	}
	sort(ord, ord + n + 1, [&](int const &u, int const &v) {
		return cross2(u, v) > 0;
	});
	for(int i = 0; i <= n; ++i) {
		int o = ord[i];
		if(!o)
			continue;
		for( ; tot > 1 && cross3(stk[tot - 2], stk[tot - 1], o) <= 0; --tot);
		if(!tot || cross2(stk[tot - 1], o)) {
			stk[tot++] = o;
		} else if(a[stk[tot - 1]] < a[o]) {
			stk[tot - 1] = o;
		}
	}
	for( ; tot > 1 && b[stk[tot - 1]] - b[stk[tot - 2]] < 0; --tot);
	int sta = 0;
	for( ; sta + 1 < tot && a[stk[sta]] - a[stk[sta + 1]] < 0; ++sta);
	double ans = max(a[0] / (double)a[stk[sta]], b[0] / (double)b[stk[tot - 1]]);
	for(int i = sta, j = i + 1; j < tot; i = j, ++j)
		ans = max(ans, ((LL)a[0] * (b[stk[j]] - b[stk[i]]) + (LL)b[0] * (a[stk[i]] - a[stk[j]])) / (double)cross2(stk[i], stk[j]));
	printf("%.7f\n", ans);
	return 0;
}