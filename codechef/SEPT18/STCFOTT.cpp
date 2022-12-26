#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int maxn = 481, maxd = 21, mod = 998244353;
int n, m, q, mx, inv[maxn], seq[maxn], mat[maxd][maxn][maxn], sum[maxd][maxn][maxn], ans[1][maxn], tmp[2][1][maxn];
void mat_add(int r, int c, int (*lft)[maxn], int (*rht)[maxn], int (*res)[maxn]) {
	for(int i = 0; i < r; ++i)
		for(int j = 0; j < c; ++j)
			(res[i][j] = lft[i][j] + rht[i][j]) >= mod && (res[i][j] -= mod);
}
void mat_mul(int r, int m, int c, int (*lft)[maxn], int (*rht)[maxn], int (*res)[maxn]) {
	static LL tmp[maxn][maxn];
	for(int i = 0; i < r; ++i)
		for(int j = 0; j < c; ++j)
			tmp[i][j] = 0;
	for(int i = 0; i < r; ++i)
		for(int j = 0; j < m; ++j) if(lft[i][j])
			for(int k = 0; k < c; ++k) if(rht[j][k])
				if((tmp[i][k] += (LL)lft[i][j] * rht[j][k]) < 0)
					tmp[i][k] = (ULL)tmp[i][k] % mod;
	for(int i = 0; i < r; ++i)
		for(int j = 0; j < c; ++j)
			res[i][j] = tmp[i][j] < mod ? tmp[i][j] : tmp[i][j] % mod;
}
vector<int> e[maxn];
void dfs(int u, int fa) {
	int rem = e[u].size() - (fa >= 0);
	if(fa >= 0) {
		if(!rem)
			mat[0][u][fa ? n + fa : fa] = 1;
		else
			mat[0][n + u][fa ? n + fa : fa] = 1;
	} else if(!rem) {
		mat[0][u][u] = 1;
	}
	for(int v : e[u]) {
		if(v == fa)
			continue;
		mat[0][u][v] = inv[rem];
		dfs(v, u);
	}
}
int main() {
	scanf("%d", &n);
	inv[1] = 1;
	for(int i = 2; i <= n; ++i) {
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
		int u, v;
		scanf("%d%d", &u, &v);
		--u;
		--v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(0, -1);
	for(int i = 0; i < n << 1; ++i)
		sum[0][i][i] = 1;
	scanf("%d", &m);
	for(int i = 0; i < m; ++i)
		scanf("%d", seq + i);
	scanf("%d", &q);
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j < n << 1; ++j)
			tmp[0][0][j] = !j;
		for(int j = 0, d = q - seq[i] + 1; d > 0; ++j, d >>= 1) {
			if(!(d & 1))
				continue;
			for( ; mx < j; ++mx) {
				mat_mul(n << 1, n << 1, n << 1, mat[mx], sum[mx], sum[mx + 1]);
				mat_add(n << 1, n << 1, sum[mx], sum[mx + 1], sum[mx + 1]);
				mat_mul(n << 1, n << 1, n << 1, mat[mx], mat[mx], mat[mx + 1]);
			}
			mat_mul(1, n << 1, n << 1, tmp[0], sum[j], tmp[1]);
			mat_add(1, n << 1, ans, tmp[1], ans);
			mat_mul(1, n << 1, n << 1, tmp[0], mat[j], tmp[0]);
		}
	}
	for(int i = 0; i < n; ++i) {
		(ans[0][i] += ans[0][n + i]) >= mod && (ans[0][i] -= mod);
		printf("%d%c", ans[0][i], " \n"[i == n - 1]);
	}
	return 0;
}
