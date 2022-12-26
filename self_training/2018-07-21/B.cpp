#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
int n, tot, a[maxn], b[maxn], fa[maxn], idx[maxn];
LL f[maxn][2];
vector<int> e[maxn], p[maxn];
bool sp[maxn];
void dfs(int u) {
	f[u][0] = 0;
	f[u][1] = sp[u] ? 0 : INF;
	for(int v : e[u]) {
		dfs(v);
		LL tmp = min(f[v][1], f[v][0] + a[v] - b[v]);
		f[u][1] = min(f[u][1] + tmp, min(f[u][0], f[u][1]) + min(f[v][0], f[v][1]) + a[v]);
		f[u][0] += tmp;
	}
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = 1; i <= n; ++i)
		scanf("%d", b + i);
	for(int i = 1; i <= n; ++i)
		scanf("%d", fa + i);
	for(int i = 1; i <= n; ++i) {
		if(idx[i])
			continue;
		int j = i;
		++tot;
		for( ; !idx[j]; idx[j] = tot, j = fa[j]);
		if(idx[j] && idx[j] != tot) {
			--tot;
			for(int k = i; idx[k] != idx[j]; idx[k] = idx[j], k = fa[k]);
		}
	}
	for(int i = 1; i <= n; ++i) {
//		printf("%d%c", idx[i], " \n"[i == n]);
		p[idx[i]].push_back(i);
	}
	LL ans = 0;
	for(int i = 1; i <= tot; ++i) {
		int u = *p[i].begin();
		for( ; idx[u] == i; idx[u] = -1, u = fa[u]);
		for(int v : p[i])
			if(u != v)
				e[fa[v]].push_back(v);
		dfs(u);
		LL tmp = min(f[u][1], f[u][0] + a[u] - b[u]);
		sp[u] = 1;
		sp[fa[u]] = 1;
		dfs(u);
		tmp = min(tmp, min(f[u][0], f[u][1]) + a[u]);
		ans += tmp;
	}
	printf("%lld\n", ans);
	return 0;
}
