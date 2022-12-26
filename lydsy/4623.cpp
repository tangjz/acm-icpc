#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef int Vector[3];
typedef int Matrix[3][3];
const int maxn = (int)1e5 + 3, maxm = (int)1e6 + 3, maxd = 17, maxv = (int)19e5 + 3, mod = (int)1e9 + 7;
int n, m, a[maxn], ord[maxn], dep[maxn], lnk[maxn];
struct Edge {
	int nxt, v;
} e[maxn << 1 | 1];
struct SparseTable {
	int fa;
	Matrix up, down;
} st[maxd][maxn];
int tot, *pr = (int *)st[1], *d = pr + (maxm >> 3 | 1), *inv = d + maxm;
inline int mod_fix(LL x) {
	if(x < -mod || x >= mod)
		x %= mod;
	return x < 0 ? x + mod : x;
}
inline void vecMul(Matrix &a, Vector &b, Vector &c) {
	static LL num[3];
	memset(num, 0, sizeof num);
	for(int i = 0; i < 3; ++i) {
		num[0] += (LL)a[0][i] * b[i];
		num[1] += (LL)a[1][i] * b[i];
		num[2] += (LL)a[2][i] * b[i];
	}
	c[0] = mod_fix(num[0]);
	c[1] = mod_fix(num[1]);
	c[2] = mod_fix(num[2]);
}
inline void matMul(Matrix &a, Matrix &b, Matrix &c) {
	static LL num[3][3];
	memset(num, 0, sizeof num);
	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j) {
			num[i][0] += (LL)a[i][j] * b[j][0];
			num[i][1] += (LL)a[i][j] * b[j][1];
			num[i][2] += (LL)a[i][j] * b[j][2];
		}
	for(int i = 0; i < 3; ++i)
		for(int j = 0; j < 3; ++j)
			c[i][j] = mod_fix(num[i][j]);
}
int val, *c = inv + maxv;
int dfs(int u) {
	ord[++tot] = u;
	val = (LL)val * a[u] % mod;
	for(int tmp = a[u]; tmp > 1; ) {
		int id = d[tmp], cc = 0;
		do tmp /= pr[id], ++cc; while(d[tmp] == id);
		val = (LL)val * inv[c[id] + 1] % mod * (c[id] + cc + 1) % mod;
		c[id] += cc;
	}
	int usz = 1;
	for(int it = lnk[u]; it; it = e[it].nxt) {
		int v = e[it].v;
		if(v == st[0][u].fa)
			continue;
		dep[v] = dep[u] + 1;
		st[0][v].fa = u;
		usz += dfs(v);
	}
	assert(val);
	st[0][u].up[1][2] = val;
	st[0][u].up[2][1] = mod - val;
	st[0][u].up[2][0] = u << 2;
	st[0][u].up[0][2] = mod - (u << 2);
	st[0][u].up[0][1] = usz;
	st[0][u].up[1][0] = mod - usz;
	st[0][u].up[0][0] = st[0][u].up[1][1] = st[0][u].up[2][2] = 0;
	memcpy(st[0][u].down, st[0][u].up, sizeof(Matrix));
	val = (LL)val * inv[a[u]] % mod;
	for(int tmp = a[u]; tmp > 1; ) {
		int id = d[tmp], cc = 0;
		do tmp /= pr[id], ++cc; while(d[tmp] == id);
		val = (LL)val * inv[c[id] + 1] % mod * (c[id] - cc + 1) % mod;
		c[id] -= cc;
	}
	return usz;
}
int mx;
int lca(int u, int v) {
	for(int i = dep[u] - dep[v], j = 0; i > 0; i >>= 1, ++j)
		(i & 1) && (u = st[j][u].fa);
	for(int i = dep[v] - dep[u], j = 0; i > 0; i >>= 1, ++j)
		(i & 1) && (v = st[j][v].fa);
	if(u == v)
		return u;
	for(int i = mx - 1; i >= 0; --i)
		if(st[i][u].fa != st[i][v].fa) {
			u = st[i][u].fa;
			v = st[i][v].fa;
		}
	return st[0][u].fa;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		for( ; 1 << mx <= a[i]; ++mx);
	}
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[i << 1] = (Edge){lnk[u], v};
		lnk[u] = i << 1;
		e[i << 1 | 1] = (Edge){lnk[v], u};
		lnk[v] = i << 1 | 1;
	}
	inv[1] = 1;
	for(int i = 2, iLim = max(min(1 << mx, maxm) - 1, n * (mx - 1)); i <= iLim; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	for(int i = 2, iLim = min(1 << mx, maxm) - 1; i <= iLim; ++i) {
		if(!d[i]) {
			pr[++tot] = i;
			d[i] = tot;
		}
		for(int j = 1, k; (k = i * pr[j]) <= iLim; ++j) {
			d[k] = j;
			if(d[i] == j)
				break;
		}
	}
	tot = 0;
	val = 1;
	dep[0] = -1;
	dep[1] = 0;
	dfs(1);
	memset(pr, 0, (c + (maxm >> 3 | 1) - pr) * sizeof(int));
	for(mx = 0; 1 << mx <= n; ++mx);
	for(int i = 1; i <= n; ++i) {
		int u = ord[i];
		for(int j = 0; j + 1 < mx && st[j][u].fa; ++j) {
			int p = st[j][u].fa;
			st[j + 1][u].fa = st[j][p].fa;
			matMul(st[j][u].up, st[j][p].up, st[j + 1][u].up);
			matMul(st[j][p].down, st[j][u].down, st[j + 1][u].down);
		}
	}
	while(m--) {
		int u, v;
		scanf("%d%d", &u, &v);
		int pp = lca(u, v);
		Vector prd = {st[0][u].up[1][2], st[0][u].up[2][0], st[0][u].up[0][1]};
		u = st[0][u].fa;
		for(int i = dep[u] - dep[pp] + 1, j = 0; i > 0; i >>= 1, ++j)
			if(i & 1) {
				vecMul(st[j][u].down, prd, prd);
				u = st[j][u].fa;
			}
		int tot = 0;
		static int que[maxd][2];
		for(int i = dep[v] - dep[pp], j = 0; i > 0; i >>= 1, ++j)
			if(i & 1) {
				que[tot][0] = j;
				que[tot++][1] = v;
				v = st[j][v].fa;
			}
		while(tot--)
			vecMul(st[que[tot][0]][que[tot][1]].up, prd, prd);
		printf("%d %d %d\n", prd[0], prd[1], prd[2]);
	}
	return 0;
}
