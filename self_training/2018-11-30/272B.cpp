#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)5e5 + 1;
int n, a[maxn], lnk[maxn], ord[maxn], fa[maxn], sz[maxn];
struct Edge {
	int nxt, v;
} e[maxn << 1 | 1];
int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[i << 1] = (Edge){lnk[u], v};
		lnk[u] = i << 1;
		e[i << 1 | 1] = (Edge){lnk[v], u};
		lnk[v] = i << 1 | 1;
	}
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	ord[1] = 1;
	for(int i = 1, tot = 1; i <= tot; ++i) {
		int u = ord[i];
		for(int it = lnk[u]; it; it = e[it].nxt) {
			int v = e[it].v;
			if(v == fa[u])
				continue;
			fa[v] = u;
			ord[++tot] = v;
		}
	}
	int ans = 0, odd = (n * (n - 1LL) / 2) & 1;
	for(int i = n; i >= 1; --i) {
		int u = ord[i], chk = odd;
		sz[u] = 1;
		for(int it = lnk[u]; it; it = e[it].nxt) {
			int v = e[it].v;
			if(v == fa[u])
				continue;
			sz[u] += sz[v];
			chk ^= (sz[v] * (sz[v] - 1LL) / 2) & 1;
		}
		chk ^= ((n - sz[u]) * (n - sz[u] - 1LL) / 2) & 1;
		if(chk)
			ans ^= a[u];
	}
	printf("%d\n", ans);
	return 0;
}
