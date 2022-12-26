#include <bits/stdc++.h>
using namespace std;
const int maxn = 101, INF = 0x3f3f3f3f;
int t, n, m, dsu[maxn], ans[maxn];
struct Edge {
	int u, v, w, typ;
	void read() {
		char ch;
		scanf("%d%d%d %c", &u, &v, &w, &ch);
		typ = ch == 'R' ? 1 : (ch == 'G' ? 2 : 4);
	}
	bool operator < (Edge const &t) const {
		return w < t.w;
	}
} e[maxn];
int dsu_find(int x) {
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
bool dsu_merge(int u, int v) {
	u = dsu_find(u);
	v = dsu_find(v);
	if(u == v)
		return 0;
	if(dsu[u] < dsu[v])
		swap(u, v);
	dsu[v] -= dsu[u] == dsu[v];
	dsu[u] = v;
	return 1;
}
void solve(int msk) {
	int cnt = 0, sum = 0;
	static bool vis[maxn];
	memset(vis, 0, m * sizeof(bool));
	memset(dsu + 1, -1, n * sizeof(int));
	for(int i = 0; i < m; ++i)
		if((e[i].typ & msk) && dsu_merge(e[i].u, e[i].v)) {
			++cnt;
			sum += e[i].w;
			vis[i] = 1;
		}
	if(cnt < n - 1)
		return;
	(ans[cnt] > sum) && (ans[cnt] = sum);
	for(int i = 0; i < m; ++i)
		if(!vis[i]) {
			++cnt;
			sum += e[i].w;
			vis[i] = 1;
			(ans[cnt] > sum) && (ans[cnt] = sum);
		}
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i < m; ++i)
			e[i].read();
		sort(e, e + m);
		memset(ans + 1, 0x3f, m * sizeof(int));
		solve(3);
		solve(6);
		printf("Case #%d:\n", Case);
		for(int i = 1; i <= m; ++i)
			printf("%d\n", ans[i] < INF ? ans[i] : -1);
	}
	return 0;
}
