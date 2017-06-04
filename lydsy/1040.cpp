#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 1000001;
int n, a[maxn], dsu[maxn], tot, seq[maxn];
std::vector<int> e[maxn];
long long f[maxn], g[maxn], ans;
int dsu_find(int x) {
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
bool dsu_merge(int u, int v) {
	if((u = dsu_find(u)) == (v = dsu_find(v)))
		return 0;
	if(dsu[u] > dsu[v])
		std::swap(u, v);
	if(dsu[u] == dsu[v])
		--dsu[u];
	dsu[v] = u;
	return 1;
}
void dfs(int u, int fa) {
	f[u] = a[u];
	g[u] = 0;
	for(std::vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
		if((*it) == fa)
			continue;
		dfs(*it, u);
		f[u] += g[*it];
		g[u] += std::max(f[*it], g[*it]);
	}
}
int main() {
	scanf("%d", &n);
	memset(dsu, -1, n * sizeof(int));
	for(int i = 0, j; i < n; ++i) {
		scanf("%d%d", a + i, &j);
		if(dsu_merge(i, --j)) {
			e[i].push_back(j);
			e[j].push_back(i);
		} else {
			seq[tot++] = i;
			seq[tot++] = j;
		}
	}
	for(int i = 0; i < tot; i += 2) {
		dfs(seq[i], -1);
		long long tmp = g[seq[i]];
		dfs(seq[i + 1], -1);
		ans += std::max(tmp, g[seq[i + 1]]);
	}
	printf("%lld\n", ans);
	return 0;
}
