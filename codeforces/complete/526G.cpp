#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, maxd = 17;
int n, ord[maxn];
vector<pair<int, int> > e[maxn];
void bfs(int rt, int fa[], int dis[]) {
	fa[rt] = dis[rt] = dis[0] = 0;
	ord[1] = rt;
	for(int i = 1, tot = 1; i <= tot; ++i) {
		int u = ord[i];
		for(auto &it : e[u]) {
			int v = it.first, w = it.second;
			if(v == fa[u])
				continue;
			fa[v] = u;
			dis[v] = dis[u] + w;
			ord[++tot] = v;
		}
	}
}
class Solver {
public:
	int tot, que[maxn], ans[maxn];
	int dis[maxn], ref[maxn], mx, fa[maxd][maxn];
	void init(int rt) {
		bfs(rt, fa[0], dis);
		for(mx = 1; 1 << mx <= n; ++mx)
			for(int j = 1; j <= n; ++j)
				fa[mx][j] = fa[mx - 1][fa[mx - 1][j]];
		static int val[maxn];
		for(int i = n; i >= 1; --i) {
			int u = ord[i], &p = ref[u] = u;
			for(auto &it : e[u]) {
				int v = it.first;
				if(v == fa[0][u])
					continue;
				if(dis[ref[v]] > dis[p])
					p = ref[v];
			}
			if(p == u) {
				que[++tot] = u;
				val[p] = 0;
			}
			val[p] = max(val[p], dis[p] - dis[fa[0][u]]);
		}
		auto cmp = [&](int const &u, int const &v) {
			return val[u] > val[v] || (val[u] == val[v] && u < v);
		};
		sort(que + 1, que + tot + 1, cmp);
		for(int i = 1; i <= n; ++i)
			ref[i] = lower_bound(que + 1, que + tot + 1, ref[i], cmp) - que;
		for(int i = 1; i <= tot; ++i)
			ans[i] = ans[i - 1] + val[que[i]];
	}
	int query(int x, int y) {
		y = min(y + y - 1, tot);
		if(ref[x] <= y)
			return ans[y];
		int p = x;
		for(int i = mx - 1; i >= 0; --i)
			if(ref[fa[i][p]] > y)
				p = fa[i][p];
		p = fa[0][p];
		return max(ans[y - 1] + dis[que[ref[x]]] - dis[p], ans[y] - dis[que[ref[p]]] + dis[que[ref[x]]]);
	}
} A, B;
int main() {
	int q;
	scanf("%d%d", &n, &q);
	for(int i = 1; i < n; ++i) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		e[u].push_back(make_pair(v, w));
		e[v].push_back(make_pair(u, w));
	}
	bfs(1, A.fa[0], A.dis);
	auto getFarthest = [&](int dis[]) {
		int ret = 1;
		for(int i = 2; i <= n; ++i)
			if(dis[i] > dis[ret])
				ret = i;
		return ret;
	};
	A.init(getFarthest(A.dis));
	B.init(getFarthest(A.dis));
	while(q--) {
		int x, y;
		static int las = 0;
		scanf("%d%d", &x, &y);
		x = (x + las - 1) % n + 1;
		y = (y + las - 1) % n + 1;
		las = max(A.query(x, y), B.query(x, y));
		printf("%d\n", las);
	}
	return 0;
}