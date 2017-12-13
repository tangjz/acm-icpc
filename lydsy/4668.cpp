#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 500001, INF = 0x3f3f3f3f;
int n, m, dsu[maxn], dep[maxn], val[maxn];
inline int dsu_find(int x) {
	if(dsu[x] < 0)
		return x;
	int y = dsu_find(dsu[x]);
	dep[x] = dep[dsu[x]] + 1;
	return y;
}
int main() {
	scanf("%d%d", &n, &m);
	memset(dsu + 1, -1, n * sizeof(int));
	for(int i = 1, j = 0, last = 0; i <= m; ++i) {
		int typ, u, v;
		scanf("%d%d%d", &typ, &u, &v);
		u ^= last;
		v ^= last;
		if(!typ) {
			++j;
			u = dsu_find(u);
			v = dsu_find(v);
			if(u == v)
				continue;
			if(dsu[u] < dsu[v])
				std::swap(u, v);
			if(dsu[u] == dsu[v])
				--dsu[v];
			dsu[u] = v;
			val[u] = j;
		} else {
			int ans = 0;
			if(dsu_find(u) == dsu_find(v)) {
				for( ; dep[v] < dep[u]; ans = std::max(ans, val[u]), u = dsu[u]);
				for( ; dep[u] < dep[v]; ans = std::max(ans, val[v]), v = dsu[v]);
				for( ; u != v; ans = std::max(ans, std::max(val[u], val[v])), u = dsu[u], v = dsu[v]);
			}
			printf("%d\n", last = ans);
		}
	}
	return 0;
}
