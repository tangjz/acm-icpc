#include <set>
#include <list>
#include <vector>
#include <cstdio>
using namespace std;
const int maxn = (int)1e3 + 1;
int n, rt, a[maxn], c[maxn], fa[maxn], dsu[maxn];
list<int> seq[maxn];
vector<int> e[maxn];
struct Node {
	int id;
	bool operator < (Node const &t) const {
		int dt = c[id] * seq[t.id].size() - c[t.id] * seq[id].size();
		return dt < 0 || (!dt && id < t.id);
	}
};
void dfs(int u) {
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
		if(*it == fa[u])
			continue;
		fa[*it] = u;
		dfs(*it);
	}
}
int dsu_find(int u) {
	return dsu[u] < 0 ? u : (dsu[u] = dsu_find(dsu[u]));
}
int main() {
	while(scanf("%d%d", &n, &rt) == 2 && !(!n && !rt)) {
		set<Node> Q;
		for(int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			c[i] = a[i];
			dsu[i] = -1;
			list<int>().swap(seq[i]);
			seq[i].push_back(a[i]);
			vector<int>().swap(e[i]);
			if(i != rt)
				Q.insert((Node){i});
		}
		for(int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		fa[rt] = 0;
		dfs(rt);
		for(int i = 1; i < n; ++i) {
			int u = Q.rbegin() -> id;
			Q.erase((Node){u});
			int p = dsu_find(fa[u]);
			if(p != rt)
				Q.erase((Node){p});
			dsu[u] = p;
			c[p] += c[u];
			seq[p].splice(seq[p].end(), seq[u]);
			if(p != rt)
				Q.insert((Node){p});
		}
		int ans = 0, sum = 0;
		for(int i = 1; i <= n; ++i) {
			sum += seq[rt].back();
			seq[rt].pop_back();
			ans += sum;
		}
		printf("%d\n", ans);
	}
	return 0;
}