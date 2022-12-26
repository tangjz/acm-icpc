#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e5 + 3, maxd = 19;
int n, mx, seq[maxn], in[maxn], out[maxn], dep[maxn], fa[maxd][maxn];
vector<int> e[maxn];
int lca(int u, int v) {
	for(int i = 0, j = dep[u] - dep[v]; j > 0; ++i, j >>= 1)
		(j & 1) && (u = fa[i][u]);
	for(int i = 0, j = dep[v] - dep[u]; j > 0; ++i, j >>= 1)
		(j & 1) && (v = fa[i][v]);
	if(u == v)
		return u;
	for(int i = mx - 1; i >= 0; --i)
		if(fa[i][u] != fa[i][v]) {
			u = fa[i][u];
			v = fa[i][v];
		}
	return fa[0][u];
}
struct Diameter {
	int u, v, d;
	Diameter() {}
	Diameter(int u) : u(u), v(u), d(0) {}
	Diameter(int u, int v) : u(u), v(v) {
		d = dep[u] + dep[v] - (dep[lca(u, v)] << 1);
	}
	bool operator < (Diameter const &t) const {
		return d < t.d;
	}
	Diameter operator + (int const &t) const {
		return max(*this, max(Diameter(u, t), Diameter(v, t)));
	}
	Diameter operator + (Diameter const &t) const {
		return max(*this, max(t, max(Diameter(u, t.u), max(Diameter(u, t.v), max(Diameter(v, t.u), Diameter(v, t.v))))));
	}
} pre[maxn], suf[maxn], out1, out2;
void pfs(int u) {
	seq[++mx] = u;
	in[u] = mx;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
		int v = *it;
		if(v == fa[0][u])
			continue;
		dep[v] = dep[u] + 1;
		fa[0][v] = u;
		pfs(v);
	}
	out[u] = mx;
}
int ans;
Diameter dfs(int u) {
	Diameter ret = u, tmp;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
		int v = *it;
		if(v == fa[0][u])
			continue;
		ret = ret + dfs(v);
	}
	if(in[u] > 1) {
		tmp = pre[in[u] - 1];
		if(out[u] < n)
			tmp = tmp + suf[out[u] + 1];
		int dis = (max(ret.d, tmp.d) + 1) >> 1;
		if(dis < ans) {
			ans = dis;
			out1 = ret;
			out2 = tmp;
		}
	} else if(out[u] < n) {
		tmp = suf[out[u] + 1];
		int dis = (max(ret.d, tmp.d) + 1) >> 1;
		if(dis < ans) {
			ans = dis;
			out1 = ret;
			out2 = tmp;
		}
	}
	return ret;
}
int getMid(Diameter dia) {
	int u = dep[dia.u] < dep[dia.v] ? dia.v : dia.u;
	for(int i = 0, j = dia.d >> 1; j > 0; ++i, j >>= 1)
		(j & 1) && (u = fa[i][u]);
	return u;
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	pfs(1);
	for(mx = 0; 1 << mx <= n; ++mx);
	for(int i = 1; i < mx; ++i)
		for(int j = 1; j <= n; ++j)
			fa[i][j] = fa[i - 1][fa[i - 1][j]];
	pre[1] = seq[1];
	for(int i = 2; i <= n; ++i)
		pre[i] = pre[i - 1] + seq[i];
	suf[n] = seq[n];
	for(int i = n - 1; i >= 1; --i)
		suf[i] = suf[i + 1] + seq[i];
	ans = n;
	dfs(1);
	printf("%d %d\n", getMid(out1), getMid(out2));
	return 0;
}
