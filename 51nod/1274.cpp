#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn = (int)5e4 + 1;
int n, m, f[maxn];
struct Edge {
	int u, v, w;
	void read() {
		scanf("%d%d%d", &u, &v, &w);
	}
	bool operator < (Edge const &t) const {
		return w < t.w;
	}
} e[maxn];
void upd(int &x, int y) {
	x < y && (x = y);
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i)
		e[i].read();
	sort(e, e + m);
	for(int i = 0; i < m; ) {
		int tot = 0;
		static pair<int, int> g[maxn << 1 | 1];
		for(int w = e[i].w; i < m && e[i].w == w; ++i) {
			g[tot++] = make_pair(e[i].u, f[e[i].v] + 1);
			g[tot++] = make_pair(e[i].v, f[e[i].u] + 1);
		}
		while(tot--) {
			int x = g[tot].first, v = g[tot].second;
			upd(f[x], v);
		}
	}
	int mx = 0;
	for(int i = 0; i < n; ++i)
		upd(mx, f[i]);
	printf("%d\n", mx);
	return 0;
}