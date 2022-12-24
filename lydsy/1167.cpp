#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)3e5 + 1;
int n, a[maxn], lnk[maxn], fa[maxn], ord[maxn], idx[maxn];
LL m;
struct Edge {
	int nxt, v;
} e[maxn << 1 | 1];
struct Node {
	int dis, pre, pos;
	bool operator < (Node const &t) const {
		return dis < t.dis || (dis == t.dis && pos > t.pos);
	}
} f[2][maxn];
int main() {
	scanf("%d%lld", &n, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[i << 1] = (Edge){lnk[u], v};
		lnk[u] = i << 1;
		e[i << 1 | 1] = (Edge){lnk[v], u};
		lnk[v] = i << 1 | 1;
	}
	ord[1] = 1;
	for(int i = 1, tot = 1; i <= tot; ++i) {
		int u = ord[i];
		for(int it = lnk[u]; it; it = e[it].nxt)
			if(e[it].v != fa[u]) {
				fa[e[it].v] = u;
				ord[++tot] = e[it].v;
			}
	}
	a[0] = -maxn;
	for(int i = n; i >= 1; --i) {
		int u = ord[i];
		f[0][u] = f[1][u] = (Node){a[0], 0, 0};
		for(int it = lnk[u]; it; it = e[it].nxt) {
			int v = e[it].v;
			if(v == fa[u])
				continue;
			Node tmp = max(f[0][v], (Node){a[v], v, v});
			--tmp.dis;
			tmp.pre = v;
			if(f[0][u] < tmp)
				swap(f[0][u], tmp);
			if(f[1][u] < tmp)
				swap(f[1][u], tmp);
		}
	}
	for(int i = 1; i <= n; ++i) {
		int u = ord[i];
		for(int it = lnk[u]; it; it = e[it].nxt) {
			int v = e[it].v;
			if(v == fa[u])
				continue;
			Node tmp = max(f[0][u].pre == v ? f[1][u] : f[0][u], (Node){a[u], u, u});
			--tmp.dis;
			tmp.pre = u;
			if(f[0][v] < tmp)
				swap(f[0][v], tmp);
			if(f[1][v] < tmp)
				swap(f[1][v], tmp);
		}
	}
	for(int i = 1, j = f[0][1].pos; i <= n; ++i, j = f[0][j].pos) {
		if(i == m) {
			printf("%d\n", j);
			break;
		}
		if(idx[j]) {
			m = (m - i) % (i - idx[j]) + i;
			for( ; i < m; ++i, j = f[0][j].pos);
			printf("%d\n", j);
			break;
		}
		idx[j] = i;
	}
	return 0;
}
