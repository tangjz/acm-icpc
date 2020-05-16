#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)3e5 + 1;
int n, m, x[maxn], y[maxn], ord[maxn], rnk[maxn];
vector<int> e[maxn];
LL sx[maxn], sy[maxn];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d", x + i, y + i);
		ord[i] = i;
	}
	while(m--) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	sort(ord + 1, ord + n + 1, [&](int const &u, int const &v) {
		return x[u] - y[u] < x[v] - y[v];
	});
	for(int i = 1; i <= n; ++i) {
		int o = ord[i];
		sx[i] = sx[i - 1] + x[o];
		sy[i] = sy[i - 1] + y[o];
		rnk[ord[i]] = i;
	}
	for(int i = 1; i <= n; ++i) {
		int pos = rnk[i];
		LL ans = 0;
		ans += (LL)(n - pos) * x[i] + (sy[n] - sy[pos]);
		ans += sx[pos - 1] + (LL)(pos - 1) * y[i];
		for(int j : e[i])
			ans -= min(x[i] + y[j], x[j] + y[i]);
		printf("%lld%c", ans, " \n"[i == n]);
	}
	return 0;
}