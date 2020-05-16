#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e4 + 1, maxm = (int)3e4 + 1, maxw = 400 * 3 + 1, mod = (int)1e9 + 7, inv6 = (mod + 1) / 6;
int inv[maxw], iact[maxw], pw[maxw][maxw];
int t, n, m, w, deg[maxn], rnk[maxn], ord[maxn], a[maxn], f[3][maxn], poly[maxw];
vector<int> e[maxn], g[maxn];
int main() {
	inv[1] = pw[0][0] = 1;
	for(int i = 2; i < maxw; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	iact[0] = 1;
	for(int i = 1; i < maxw; ++i) {
		pw[i][0] = 1;
		iact[i] = (LL)iact[i - 1] * inv[i] % mod;
		for(int j = 1; j < maxw; ++j)
			pw[i][j] = (LL)pw[i][j - 1] * i % mod;
	}
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d%d", &n, &m, &w);
		w *= 3;
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		while(m--) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			++deg[v];
		}
		m = 0;
		for(int i = 1; i <= n; ++i)
			if(!deg[i])
				ord[++m] = i;
		for(int i = 1; i <= m; ++i) {
			int u = ord[i];
			rnk[u] = i;
			for(int v : e[u])
				if(!(--deg[v]))
					ord[++m] = v;
		}
		assert(n == m);
		for(int i = 1; i <= n; ++i) {
			int u = ord[i];
			vector<int>().swap(g[i]);
			g[i].reserve(e[u].size());
			for(int v : e[u])
				g[i].push_back(rnk[v]);
			vector<int>().swap(e[u]);
			sort(g[i].begin(), g[i].end());
		}
		memset(poly, 0, (w + 1) * sizeof(int));
		for(int i = 1; i <= w; ++i) {
			int *cpw = pw[i], cnt = 0;
			for(int j = n; j >= 1; --j) {
				int u = ord[j];
				f[0][j] = cpw[a[u]];
				f[1][j] = cpw[a[u] + a[u]];
				f[2][j] = cpw[a[u] + a[u] + a[u]];
				for(int k : g[j]) {
					(f[0][j] += f[0][k]) >= mod && (f[0][j] -= mod);
					(f[1][j] += f[1][k]) >= mod && (f[1][j] -= mod);
					(f[2][j] += f[2][k]) >= mod && (f[2][j] -= mod);
				}
				cnt = (cnt + ((LL)f[0][j] * f[0][j] - 3LL * f[1][j]) % mod * f[0][j] + 2LL * f[2][j]) % mod;
			}
			if(!cnt)
				continue;
			int coeff = cnt < 0 ? cnt + mod : cnt, prd = inv[i];
			coeff = (LL)coeff * inv6 % mod * iact[i] % mod * iact[w - i] % mod;
			if(!((w - i) & 1))
				coeff = mod - coeff;
			for(int j = 0; j <= w; ++j) {
				coeff = (LL)coeff * prd % mod;
				(poly[j] += coeff) >= mod && (poly[j] -= mod);
			}
		}
		for(int i = 0; i <= w; ++i)
			for(int j = w; j >= 0; --j)
				poly[j] = ((j ? poly[j - 1] : 0) - (LL)i * poly[j]) % mod;
		printf("Case #%d: ", Case);
		for(int i = 1; i <= w; ++i)
			printf("%d%c", poly[i] < 0 ? poly[i] + mod : poly[i], " \n"[i == w]);
	}
	return 0;
}
