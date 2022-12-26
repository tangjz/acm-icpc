#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
int t, n, fa[maxn], dsu[maxn];
vector<int> e[maxn];
inline int sgn(LL x) {
	return (x > 0) - (x < 0);
}
struct Info {
	bool good;
	LL dec, inc;
	int compareTo(Info const &t) const {
		if(good != t.good)
			return t.good - good;
		return good ? sgn(dec - t.dec) : sgn(t.inc - inc);
	}
} a[maxn];
struct Node {
	int id;
	bool operator < (Node const &t) const {
		int diff = a[id].compareTo(a[t.id]);
		return diff < 0 || (!diff && id < t.id);
	}
};
void dfs(int u) {
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
		int v = *it;
		if(v != fa[u]) {
			fa[v] = u;
			dfs(v);
		}
	}
}
int dsu_find(int u) {
	return dsu[u] < 0 ? u : (dsu[u] = dsu_find(dsu[u]));
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		set<Node> Q;
		a[1] = (Info){0, 0LL, 0LL};
		for(int i = 2; i <= n; ++i) {
			int x, y;
			scanf("%d%d", &x, &y);
			a[i] = (Info){x < y, (LL)x, (LL)y};
			Q.insert((Node){i});
		}
		for(int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		fa[1] = 0;
		dfs(1);
		memset(dsu + 1, -1, n * sizeof(int));
		for(int i = 1; i < n; ++i) {
			int u = Q.begin() -> id;
			Q.erase((Node){u});
			int p = dsu_find(fa[u]);
			if(p > 1)
				Q.erase((Node){p});
			dsu[u] = p;
			LL diff = a[p].inc - a[u].dec;
			if(diff < 0) {
				a[p].dec -= diff;
				a[p].inc = a[u].inc;
			} else {
				a[p].inc = diff + a[u].inc;
			}
			a[p].good = a[p].dec < a[p].inc;
			if(p > 1)
				Q.insert((Node){p});
		}
		printf("%lld\n", a[1].dec);
		for(int i = 1; i <= n; ++i)
			vector<int>().swap(e[i]);
	}
	return 0;
}
