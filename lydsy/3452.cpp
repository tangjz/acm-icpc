#include <bits/stdc++.h>
typedef double DB;
const int maxn = 11, maxd = 10, maxs = 15, maxl = 6;
int n, m, e, sz, idx[maxn], fail[maxn], nxt[maxn][maxd + 1];
DB lpw[maxd + 1][maxs], c[maxs][maxs];
void init() {
	int t, L = 0, R = 0, que[maxn];
	char buf[5];
	scanf("%d", &t);
	n = 1;
	while(t--) {
		scanf("%s", buf);
		int rt = 0;
		for(int i = 0; buf[i]; ++i) {
			int o = buf[i] - '0';
			if(!nxt[rt][o])
				nxt[rt][o] = n++;
			rt = nxt[rt][o];
		}
		idx[rt] = -1;
	}
	for(int i = 0; i < maxd; ++i)
		if(nxt[0][i])
			que[R++] = nxt[0][i];
	m = 1;
	while(L < R) {
		int u = que[L++];
		if(idx[u] != -1)
			idx[u] = m++;
		for(int i = 0; i < maxd; ++i) {
			if(!nxt[u][i])
				continue;
			int v = nxt[u][i], p = fail[u];
			for( ; p && !nxt[p][i]; p = fail[p]);
			fail[v] = nxt[p][i];
			que[R++] = v;
		}
	}
	e = (maxs - 1) / m;
	sz = e * m;
	lpw[0][0] = 0;
	for(int i = 1; i <= maxd; ++i) {
		lpw[i][0] = 0;
		lpw[i][1] = log(i);
		for(int j = 2; j < e; ++j)
			lpw[i][j] = lpw[i][j - 1] + lpw[i][1];
	}
	lpw[maxd][e] = lpw[maxd][e - 1] + lpw[maxd][1];
	for(int i = 0; i < e; ++i) {
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
	}
}
DB f[maxs], mat[maxs][maxs << 1 | 1], ans;
void dfs(int dep, int val, int msk) {
	if(idx[msk] == -1)
		return;
	if(dep == maxl) {
		msk = idx[msk];
		DB prd = 1;
		for(int i = 0; i < e; ++i)
			f[i * m + msk] += 1 / (prd *= val);
		return;
	}
	ans += 1.0 / val;
	for(int i = 0; i < maxd; ++i) {
		int nmsk = msk;
		for( ; nmsk && !nxt[nmsk][i]; nmsk = fail[nmsk]);
		dfs(dep + 1, val * maxd + i, nxt[nmsk][i]);
	}
}
void solve() {
	for(int i = 0; i < sz; ++i)
		mat[i][i] = mat[i][sz + i] = 1;
	for(int i = 0; i < n; ++i) {
		int k = idx[i];
		if(k == -1)
			continue;
		for(int d = 0; d < maxd; ++d) {
			int ii = i;
			for( ; ii && !nxt[ii][d]; ii = fail[ii]);
			ii = nxt[ii][d];
			int kk = idx[ii];
			if(kk == -1)
				continue;
			for(int j = 0; j < e; ++j)
				for(int jj = 0; jj <= j; ++jj) {
					if(!d && jj < j)
						continue;
					mat[j * m + k][jj * m + kk] -= ((j - jj) & 1 ? -1 : 1) * exp(log(c[j][jj]) + lpw[d][j - jj] - lpw[maxd][j + 1]);
				}
		}
	}
	for(int i = 0, j, k; i < sz; ++i) {
		for(j = i, k = j + 1; k < sz; ++k)
			if(fabs(mat[k][i]) > fabs(mat[j][i]))
				j = k;
//		assert(fabs(mat[j][i]) > 1e-20);
		DB prd = mat[j][i];
		for(k = i; k < sz << 1; ++k) {
			std::swap(mat[j][k], mat[i][k]);
			mat[i][k] /= prd;
		}
		for(j = 0; j < sz; ++j) {
			if(i == j)
				continue;
			DB prd = mat[j][i];
			for(int k = i; k < sz << 1; ++k)
				mat[j][k] -= prd * mat[i][k];
		}
	}
	for(int i = 1; i < maxd; ++i)
		dfs(1, i, nxt[0][i]);
	for(int i = 0; i < sz; ++i)
		for(int j = 0; j < m; ++j)
			ans += f[i] * mat[i][sz + j];
	printf("%.4f\n", (double)ans);
}
int main() {
	init();
	solve();
	return 0;
}
