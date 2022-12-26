#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
int t, n, tot, w[maxn], ord[maxn], fa[maxn];
pair<int, int> msk[maxn];
vector<int> e[maxn];
bool ban[maxn];
void bfs(int rt) { // fa[rt] was set
	tot = 0;
	ord[tot++] = rt;
	for(int i = 0; i < tot; ++i) {
		int u = ord[i];
		for(auto &v : e[u])
			if(v != fa[u] && !ban[v]) {
				fa[v] = u;
				ord[tot++] = v;
			}
	}
}
int getRoot(int rt) {
	int pos = -1, cnt = maxn;
	static int sz[maxn];
	bfs(rt);
	for(int i = tot - 1; i >= 0; --i) {
		int u = ord[i], mx = 0;
		sz[u] = 1;
		for(auto &v : e[u])
			if(v != fa[u] && !ban[v]) {
				sz[u] += sz[v];
				mx = max(mx, sz[v]);
			}
		mx = max(mx, tot - sz[u]);
		if(mx < cnt) {
			pos = u;
			cnt = mx;
		}
	}
	return pos;
}
LL solve(int m, int ord[]) {
	LL ret = 0;
	int cnt[3][3] = {}, eq[3][3] = {};
	sort(ord, ord + m, [&w](int const &u, int const &v) {
		return w[u] < w[v];
	});
	for(int i = 0; i < m; ) {
		for(int ww = w[ord[i]]; i < m && w[ord[i]] == ww; ++i) {
			pair<int, int> mask = msk[ord[i]];
			for(int x = 0; x < 3; ++x)
				for(int y = 0; y < 3; ++y) {
					if(x + mask.second < 1 || y + mask.first <= 1)
						ret += cnt[x][y];
					if(x + mask.second <= 1 || y + mask.first <= 1)
						ret += eq[x][y];
				}
			++eq[mask.first][mask.second];
		}
		for(int x = 0; x < 3; ++x)
			for(int y = 0; y < 3; ++y) {
				cnt[x][y] += eq[x][y];
				eq[x][y] = 0;
			}
	}
	return ret;
}
LL dfs(int rt) {
	LL ret = 1;
	fa[rt] = -1;
	rt = getRoot(rt);
	ban[rt] = 1;
	int qtot = 0;
	static int que[maxn];
	msk[rt] = make_pair(0, 0);
	que[qtot++] = rt;
	for(auto &u : e[rt]) {
		if(ban[u])
			continue;
		fa[u] = rt;
		bfs(u);
		for(int i = 0; i < tot; ++i) {
			int u = ord[i], p = fa[u];
			msk[u] = msk[p];
			if(w[p] < w[u])
				msk[u].first = min(msk[u].first + 1, 2);
			else if(w[p] > w[u])
				msk[u].second = min(msk[u].second + 1, 2);
			que[qtot++] = u;
		}
		LL tmp = solve(tot, ord);
		ret -= tmp;
	}
	LL tmp = solve(qtot, que);
	ret += tmp;
	for(auto &u : e[rt])
		if(!ban[u])
			ret += dfs(u);
	return ret;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			scanf("%d", w + i);
		for(int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		printf("%lld\n", dfs(1));
		for(int i = 1; i <= n; ++i) {
			ban[i] = 0;
			vector<int>().swap(e[i]);
		}
	}
	return 0;
}