#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)4e5 + 1;
int n, m, tot, dsu[maxn], lnk[maxn], pre[maxn];
struct Edge {
	int nxt, v;
} e[maxn];
bool bri[maxn];
int tarjan(int u, int Fa) {
	int lowu = pre[u] = tot++;
	for(int it = lnk[u]; it != -1; it = e[it].nxt) {
		if(Fa == (it ^ 1))
			continue;
		int &v = e[it].v;
		if(pre[v] == -1) {
			int lowv = tarjan(v, it);
			if(lowu > lowv)
				lowu = lowv;
			if(pre[u] < lowv)
				bri[it >> 1] = 1;
		} else if(lowu > pre[v])
			lowu = pre[v];
	}
	return lowu;
}
int dsu_find(int x) {
	return x == dsu[x] ? x : (dsu[x] = dsu_find(dsu[x]));
}
int main() {
	scanf("%d%d%*d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		dsu[i] = i;
		lnk[i] = -1;
	}
	vector<pair<int, pair<int, int> > > edges;
	edges.reserve(m);
	while(m--) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		edges.push_back(make_pair(w, make_pair(u, v)));
	}
	sort(edges.begin(), edges.end());
	m = 0;
	for(vector<pair<int, pair<int, int> > >::iterator it = edges.begin(); it != edges.end(); ) {
		vector<pair<int, pair<int, int> > >::iterator jt = it;
		for( ; jt != edges.end() && it -> first == jt -> first; ++jt) {
			pair<int, int> tmp = jt -> second;
			int u = dsu_find(tmp.first);
			int v = dsu_find(tmp.second);
			if(u != v) {
				e[m] = (Edge){lnk[u], v};
				lnk[u] = m++;
				e[m] = (Edge){lnk[v], u};
				lnk[v] = m++;
			}
		}
		for( ; it != jt; ++it) {
			pair<int, int> tmp = it -> second;
			int u = dsu_find(tmp.first);
			int v = dsu_find(tmp.second);
			if(u != v) {
				lnk[++n] = -1;
				dsu[n] = n;
				dsu[u] = dsu[v] = n;
			}
		}
	}
	memset(pre + 1, -1, n * sizeof(int));
	for(int i = 1; i <= n; ++i)
		if(pre[i] == -1)
			tarjan(i, -1);
	int ans = 0;
	for(int i = 0; i < m; i += 2)
		ans += bri[i >> 1];
	printf("%d\n", ans);
	return 0;
}
