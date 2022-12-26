#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 101, maxm = 301, maxs = maxn * maxn * maxn;
int n, m, gcd[maxn][maxn], inv[maxn][maxn], nxt[maxn][maxn][maxn], que[maxs], L, R;
LL tL, tR, ans[maxn];
bool f[maxn][maxn][maxn];
vector<int> e[maxn], cand[maxn];
vector<pair<int, int> > edges;
inline void mod_inc(int &x, int y, int mod) {
	(x += y) >= mod && (x -= mod);
}
LL dfs(int idx, int mod, int rem) {
	for( ; idx && cand[idx].empty(); --idx);
	if(!idx)
		return (rem <= tR ? (tR - rem) / mod + 1 : 0) - (rem < tL ? (tL - 1 - rem) / mod + 1 : 0);
	LL ret = 0;
	int com = gcd[idx][mod % idx], upp = idx / com, adt = inv[idx][mod % idx];
	int rem2 = rem % com, mul = (upp - (rem - rem2) % idx / com) * adt % upp;
	if(cand[idx].size() + 1 < idx - cand[idx].size()) {
		ret += dfs(idx - 1, mod, rem);
		for(vector<int>::iterator it = cand[idx].begin(); it != cand[idx].end(); ++it) {
			for( ; rem2 < *it; rem2 += com, mod_inc(mul, adt, upp));
			if(rem2 == *it)
				ret -= dfs(idx - 1, mod * upp, rem + mod * mul);
		}
	} else {
		for(vector<int>::iterator it = cand[idx].begin(); it != cand[idx].end(); ++it) {
			for( ; rem2 < *it; rem2 += com, mod_inc(mul, adt, upp))
				ret += dfs(idx - 1, mod * upp, rem + mod * mul);
			if(rem2 == *it) {
				rem2 += com;
				mod_inc(mul, adt, upp);
			}
		}
		for( ; rem2 < idx; rem2 += com, mod_inc(mul, adt, upp))
			ret += dfs(idx - 1, mod * upp, rem + mod * mul);
	}
	return ret;
}
inline int getID(int x, int y, int z) {
	return (y * n + x) * n + z;
}
inline void setID(int val, int &x, int &y, int &z) {
	z = val % n;
	val /= n;
	x = val % n;
	y = val / n;
}
int main() {
	scanf("%d%d%lld%lld", &n, &m, &tL, &tR);
	for(int i = 0; i < m; ++i) {
		int u, v;
		if(scanf("%d%d", &u, &v) == 2 && u <= n && v <= n) {
			edges.push_back(make_pair(--u, --v));
			e[u].push_back(v);
		}
	}
	bool *F = f[0][0], *G = f[0][1];
	F[0] = 1;
	if(!tL)
		++ans[0];
	for(int i = 1; i <= n * n && i <= tR; ++i) {
		swap(F, G);
		memset(F, 0, n * sizeof(bool));
		for(vector<pair<int, int> >::iterator it = edges.begin(); it != edges.end(); ++it)
			F[it -> second] |= G[it -> first];
		if(i >= tL)
			for(int j = 0; j < n; ++j)
				ans[j] += F[j];
	}
	if(tR <= n * n) {
		for(int i = 0; i < n; ++i)
			printf("%lld\n", ans[i]);
		return 0;
	}
	tL = max(tL, n * n + 1LL);
	memset(F, 0, n * sizeof(bool));
	memset(G, 0, n * sizeof(bool));
	for(int i = 0; i <= n; ++i) {
		gcd[0][i] = i;
		f[0][i][i] = 1;
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j <= n; ++j) {
			gcd[i][j] = i > j ? gcd[j][i] : gcd[i][j - i];
			for(vector<pair<int, int> >::iterator it = edges.begin(); it != edges.end(); ++it)
				f[i][j][it -> second] |= f[i - 1][j][it -> first];
		}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j < i; ++j)
			for(int val = 0; val != gcd[i][j]; ++inv[i][j], mod_inc(val, j, i));
	for(int i = 0; i < n; ++i) {
		static int per[maxn], st = 0, vis[maxn] = {};
		per[0] = 0;
		++st;
		for(int j = 1; j <= n; ++j)
			if(f[j][i][i] && vis[j] != st) {
				per[++per[0]] = j;
				for(int k = j; k <= n; k += j)
					vis[k] = st;
			}
		assert(per[0] <= n);
		if(!per[0])
			continue;
		for(int j = 0; j <= n; ++j) {
			++st;
			for(int k = 1; k <= per[0]; ++k) {
				int com = gcd[j][per[k]];
				assert(com <= n);
				if(vis[com] != st) {
					vis[com] = st;
					nxt[i][j][++nxt[i][j][0]] = com;
				}
			}
			assert(nxt[i][j][0] <= n);
		}
	}
	for(int i = 0; i < n; ++i) {
		memset(f[i][0], 0, n * sizeof(bool));
		for(int j = 1; j <= n; ++j)
			memset(f[i][j], 0, j * sizeof(bool));
	}
	f[0][0][0] = 1;
	que[R++] = getID(0, 0, 0);
	while(L < R) {
		int u, per, rem, tmp;
		setID(que[L++], u, per, rem);
		(tmp = rem + 1) == per && (tmp = 0);
		if(tmp < n)
			for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
				int v = *it;
				if(f[v][per][tmp])
					continue;
				f[v][per][tmp] = 1;
				que[R++] = getID(v, per, tmp);
			}
		for(int i = 1; i <= nxt[u][per][0]; ++i) {
			int com = nxt[u][per][i];
			tmp = rem < com ? rem : rem % com;
			if(f[u][com][tmp])
				continue;
			f[u][com][tmp] = 1;
			que[R++] = getID(u, com, tmp);
		}
	}
	for(int i = 0; i < n; ++i) {
		for(int j = 1; j <= n; ++j) {
			if(!cand[j].empty())
				vector<int>().swap(cand[j]);
			for(int k = 0; k < j; ++k) {
				if(!f[i][j][k])
					continue;
				cand[j].push_back(k);
				for(int x = j + j; x <= n; x += j)
					for(int y = k; y < x; y += j)
						f[i][x][y] = 0;
			}
		}
		ans[i] += tR - tL + 1 - dfs(n, 1, 0);
		printf("%lld\n", ans[i]);
	}
	return 0;
}
