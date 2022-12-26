#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e5 + 1;
int n, m, dsu[maxn], dsu2[maxn], st, tim[maxn];
struct Edge {
	int u, v, w;
} e[maxn];
inline int dsuFind(int dsu[], int x) {
	return dsu[x] < 0 ? x : (dsu[x] = dsuFind(dsu, dsu[x]));
}
inline bool dsuMerge(int dsu[], int u, int v) {
	u = dsuFind(dsu, u);
	v = dsuFind(dsu, v);
	if(u == v)
		return 0;
	if(dsu[u] < dsu[v])
		swap(u, v);
	dsu[v] -= dsu[u] == dsu[v];
	dsu[u] = v;
	return 1;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i)
		scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
	sort(e, e + m, [&](Edge const &lft, Edge const &rht) {
		return lft.w < rht.w;
	});
	LL ans = 0;
	memset(dsu + 1, -1, n * sizeof(int));
	for(int i = 0, j; i < m; ) {
		++st;
		auto enable = [&](int u) {
			if(tim[u] != st) {
				tim[u] = st;
				dsu2[u] = -1;
			}
		};
		for(j = i; j < m && e[j].w == e[i].w; ++j) {
			int u = dsuFind(dsu, e[j].u);
			int v = dsuFind(dsu, e[j].v);
			if(u == v)
				continue;
			enable(u);
			enable(v);
			if(!dsuMerge(dsu2, u, v))
				ans += e[j].w;
		}
		for( ; i < j; ++i)
			dsuMerge(dsu, e[i].u, e[i].v);
	}
	printf("%lld\n", ans);
	return 0;
}