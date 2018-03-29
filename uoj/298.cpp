#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
const LL INF = ~0ULL >> 1;
int n, dt, m, seq[maxn], fa[maxn], ord1[maxn], ord2[maxn];
LL dis[maxn], f[maxn], g[maxn];
vector<pair<int, int> > e[maxn];
bool ban[maxn];
pair<LL, int> dfs(int u) {
	pair<LL, int> ret = make_pair(dis[u], u);
	for(auto &it : e[u]) {
		int &v = it.first;
		if(v == fa[u] || ban[v])
			continue;
		fa[v] = u;
		dis[v] = dis[u] + it.second;
		ret = max(ret, dfs(v));
	}
	return ret;
}
bool solve(LL dim) {
	LL max1 = -INF, min2 = INF;
	LL low1 = -INF, upp1 = INF;
	LL low2 = -INF, upp2 = INF;
	for(int i = 1, j = 1; i <= m; ++i) {
		for( ; j <= m && ord2[j] < ord1[i] && f[ord1[i]] + g[ord1[i]] - f[ord2[j]] + g[ord2[j]] > dim; ++j) {
			max1 = max(max1, f[ord2[j]] + g[ord2[j]]);
			min2 = min(min2, f[ord2[j]] - g[ord2[j]]);
		}
		if(j == 1) // INF
			continue;
		low1 = max(low1, f[ord1[i]] + g[ord1[i]] + max1);
		upp1 = min(upp1, f[ord1[i]] - g[ord1[i]] + min2);
		low2 = max(low2, f[ord1[i]] + g[ord1[i]] - min2);
		upp2 = min(upp2, f[ord1[i]] - g[ord1[i]] - max1);
	}
	if((low1 -= dim - dt) <= (upp1 += dim - dt) && (low2 -= dim - dt) <= (upp2 += dim - dt))
		for(int i = 1, L1 = m + 1, R1 = m, L2 = 1, R2 = 0; i <= m; ++i) {
			for( ; L1 > 1 && f[i] + f[L1 - 1] >= low1; --L1);
			for( ; R1 >= 1 && f[i] + f[R1] > upp1; --R1);
			for( ; L2 <= m && f[i] - f[L2] > upp2; ++L2);
			for( ; R2 < m && f[i] - f[R2 + 1] >= low2; ++R2);
			if(max(L1, L2) <= min(R1, R2))
				return 1;
		}
	return 0;
}
int main() {
	while(scanf("%d%d", &n, &dt) == 2 && !(!n && !dt)) {
		for(int i = 1; i < n; ++i) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			e[u].push_back(make_pair(v, w));
			e[v].push_back(make_pair(u, w));
		}
		fa[1] = dis[1] = 0;
		seq[1] = dfs(1).second;
		fa[seq[1]] = dis[seq[1]] = 0;
		seq[1] = dfs(seq[1]).second;
		m = 0;
		for(int i = seq[1]; i > 0; i = fa[i]) {
			seq[++m] = i;
			f[m] = dis[seq[1]] - dis[i];
			ban[i] = 1;
		}
		for(int i = 1; i <= m; ++i) {
			fa[seq[i]] = dis[seq[i]] = 0;
			g[i] = dfs(seq[i]).first;
			ord1[i] = ord2[i] = i;
		}
		sort(ord1 + 1, ord1 + m + 1, [&](int const &u, int const &v) {
			return f[u] + g[u] < f[v] + g[v];
		});
		sort(ord2 + 1, ord2 + m + 1, [&](int const &u, int const &v) {
			return f[u] - g[u] < f[v] - g[v];
		});
		LL lft = 0, rht = f[m];
		while(lft < rht) {
			LL mid = (lft + rht) >> 1;
			solve(mid) ? (rht = mid) : (lft = mid + 1);
		}
		printf("%lld\n", lft);
		for(int i = 1; i <= n; ++i)
			vector<pair<int, int> >().swap(e[i]);
		for(int i = 1; i <= m; ++i)
			ban[seq[i]] = 0;
	}
	return 0;
}
