#include <bits/stdc++.h>
typedef long long LL;
const int maxl = 29, maxs = 1 << 8 | 1, mod = 12345678;
int n, m, all, fct[maxl], bin[maxl][maxl], ctr[maxl], tot, e[maxs], c[maxs], f[maxs];
char buf[maxl];
int dfs(int dep) {
	for( ; dep < all && ctr[dep]; ++dep);
	if(dep == all) {
		int upp = (1 << tot) - 1;
		f[0] = 1;
		for(int i = 1; i <= upp; ++i) {
			int lbt = i & -i;
			e[i] = e[lbt] | e[i ^ lbt];
			c[i] = __builtin_popcount(e[i]);
			f[i] = 0;
			for(int j = 1; j <= i; j <<= 1)
				if(i & j) {
					int k = i ^ j;
					f[i] = (f[i] + (LL)bin[c[i] - 1][c[k]] * fct[c[i] - c[k] - 1] % mod * f[k]) % mod;
				}
		}
		return (LL)bin[all][c[upp]] * fct[all - c[upp]] % mod * f[upp] % mod;
	}
	int ux = dep / m, uy = dep % m, msk = 1 << (tot++);
	e[msk] = 0;
	for(int dx = -1; dx <= 1; ++dx)
		for(int dy = -1; dy <= 1; ++dy) {
			int vx = ux + dx, vy = uy + dy;
			if(vx < 0 || vx >= n || vy < 0 || vy >= m)
				continue;
			int j = dep + dx * m + dy;
			++ctr[j];
			e[msk] |= 1 << j;
		}
	int res = dfs(dep + 1);
	for(int dx = -1; dx <= 1; ++dx)
		for(int dy = -1; dy <= 1; ++dy) {
			int vx = ux + dx, vy = uy + dy;
			if(vx < 0 || vx >= n || vy < 0 || vy >= m)
				continue;
			int j = dep + dx * m + dy;
			--ctr[j];
		}
	--tot;
	(res = dfs(dep + 1) - res) < 0 && (res += mod);
	return res;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%s", buf + i * m);
	all = n * m;
	fct[0] = bin[0][0] = 1;
	for(int i = 1; i <= all; ++i) {
		fct[i] = (LL)fct[i - 1] * i % mod;
		bin[i][0] = bin[i][i] = 1;
		for(int j = 1; j < i; ++j)
			(bin[i][j] = bin[i - 1][j - 1] + bin[i - 1][j]) >= mod && (bin[i][j] -= mod);
	}
	for(int i = 0; i < all; ++i) {
		if(buf[i] != 'X')
			continue;
		int ux = i / m, uy = i % m, msk = 1 << (tot++);
		for(int dx = -1; dx <= 1; ++dx)
			for(int dy = -1; dy <= 1; ++dy) {
				int vx = ux + dx, vy = uy + dy;
				if(vx < 0 || vx >= n || vy < 0 || vy >= m)
					continue;
				int j = i + dx * m + dy;
				if(i != j && buf[j] == 'X') {
					puts("0");
					return 0;
				}
				++ctr[j];
				e[msk] |= 1 << j;
			}
	}
	printf("%d\n", dfs(0));
	return 0;
}