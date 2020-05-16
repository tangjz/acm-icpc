#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int maxn = (int)4e3 + 1, maxh = 11, maxs = (int)2e4 + 1, maxc = 26, mod = (int)1e9 + 7;
int t, n, m, tot, val[maxs], son[maxs][maxc | 1];
int typ[maxn], dep[maxn], f[maxn][maxh][maxh << 1 | 1];
vector<int> e[maxn];
int dfs(int u) {
	vector<int> ch;
	for(int i = 0; i < maxc; ++i) {
		if(!son[u][i])
			continue;
		ch.push_back(dfs(son[u][i]));
	}
	if(!val[u] && ch.size() == 1)
		return ch.back();
	typ[++tot] = val[u];
	e[tot].swap(ch);
	return tot;
}
inline void mod_inc(LL &x, LL y) {
	(x += y) < 0 && (x = (ULL)x % mod);
}
inline int mod_fix(LL x) {
	return x < mod ? x : x % mod;
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d", &n, &m);
		tot = 0;
		val[0] = 0;
		memset(son[0], 0, sizeof son[0]);
		for(int i = 0; i < n + m; ++i) {
			int rt = 0;
			static char buf[maxh];
			scanf("%s", buf);
			for(int j = 0; buf[j]; ++j) {
				int o = buf[j] - 'a';
				if(!son[rt][o]) {
					val[++tot] = 0;
					memset(son[tot], 0, sizeof son[0]);
					son[rt][o] = tot;
				}
				rt = son[rt][o];
			}
			val[rt] = i < n ? 1 : 2;
		}
		tot = 0;
		dfs(0);
		dep[tot] = 0;
		for(int u = tot; u > 0; --u) {
			int upp = dep[u] + (typ[u] > 0);
			for(int &v : e[u])
				dep[v] = upp;
		}
		for(int u = 1; u <= tot; ++u) {
			int upp = dep[u] + (typ[u] > 0);
			for(int i = 0; i <= upp; ++i)
				for(int j = 0; j <= (upp - i) << 1; ++j)
					f[u][i][j] = 0;
			f[u][0][0] = 1;
			static LL g[maxh + 2][maxh << 1 | 1];
			for(int &v : e[u]) {
				for(int i = 0; i <= upp; ++i)
					for(int j = 0; j <= (upp - i) << 1; ++j)
						g[i][j] = 0;
				for(int i = 0; i <= upp; ++i)
					for(int j = 0; j <= (upp - i) << 1; ++j) {
						if(!f[u][i][j])
							continue;
						int upp2 = ((upp - i) << 1) - j;
						for(int p = 0; p << 1 <= upp2; ++p)
							for(int q = 0; (p << 1) + q <= upp2; ++q)
								if(f[v][p][q])
									mod_inc(g[i + p][j + q], (LL)f[u][i][j] * f[v][p][q]);
					}
				for(int i = 0; i <= upp; ++i)
					for(int j = 0; j <= (upp - i) << 1; ++j)
						f[u][i][j] = mod_fix(g[i][j]);
			}
			if(!typ[u])
				continue;
			for(int i = 0; i <= dep[u]; ++i)
				for(int j = 0; j <= (dep[u] - i) << 1; ++j)
					g[i][j] = 0;
			for(int i = 0; i <= upp; ++i)
				for(int j = 0; j <= (upp - i) << 1; ++j) {
					if(!f[u][i][j])
						continue;
					mod_inc(g[i][j], f[u][i][j]);
					if(typ[u] == 1) {
						mod_inc(g[i + 1][j], f[u][i][j]);
						mod_inc(g[i + 2][j], (f[u][i][j] + (f[u][i][j] & 1 ? mod : 0)) / 2);
						if(j) {
							mod_inc(g[i][j - 1], (LL)j * f[u][i][j]);
							mod_inc(g[i + 1][j - 1], (LL)j * f[u][i][j]);
							if(j - 1)
								mod_inc(g[i][j - 2], j * (j - 1) / 2 * (LL)f[u][i][j]);
						}
					} else {
						mod_inc(g[i][j + 1], f[u][i][j]);
						if(i)
							mod_inc(g[i - 1][j], (LL)i * f[u][i][j]);
					}
				}
			for(int i = 0; i <= upp; ++i)
				for(int j = 0; j <= (upp - i) << 1; ++j)
					f[u][i][j] = j <= (dep[u] - i) << 1 ? mod_fix(g[i][j]) : 0;
		}
		printf("Case #%d: %d\n", Case, f[tot][0][0]);
	}
	return 0;
}
