#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxd = 1 << 6 | 1, maxl = 101, maxs = 1201, mod = 998244353;
int n, m, tot, fa[maxs], nxt[2][maxs], fail[maxs], msk[maxs], que[maxs], f[2][maxd][maxs], cur, pre = 1;
inline void mod_inc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i) {
		static char buf[maxl];
		scanf("%s", buf);
		int len = strlen(buf), rt;
		for(int j = rt = 0; j < len; ++j) {
			int o = buf[j] - '0';
			if(!nxt[o][rt]) {
				fa[++tot] = rt;
				nxt[o][rt] = tot;
			}
			rt = nxt[o][rt];
		}
		msk[rt] |= 1 << i;
		for(int j = rt = 0; j < len; ++j) {
			int o = '1' - buf[len - 1 - j];
			if(!nxt[o][rt]) {
				fa[++tot] = rt;
				nxt[o][rt] = tot;
			}
			rt = nxt[o][rt];
		}
		msk[rt] |= 1 << i;
	}
	tot = 0;
	if(nxt[0][0])
		que[++tot] = nxt[0][0];
	if(nxt[1][0])
		que[++tot] = nxt[1][0];
	for(int i = 1; i <= tot; ++i) {
		int u = que[i];
		for(int o = 0; o < 2; ++o) {
			int v = nxt[o][u];
			if(!v)
				continue;
			int w = fail[u];
			for( ; w && !nxt[o][w]; w = fail[w]);
			fail[v] = nxt[o][w];
			msk[v] |= msk[fail[v]];
			que[++tot] = v;
		}
	}
	f[cur][0][0] = 1;
	for(int i = 1; i <= m; ++i) {
		swap(cur, pre);
		for(int j = 0; j < 1 << n; ++j)
			memset(f[cur][j], 0, (tot + 1) * sizeof(int));
		for(int j = 0; j < 1 << n; ++j)
			for(int x = 0; x <= tot; ++x)
				if(f[pre][j][x])
					for(int o = 0; o < 2; ++o) {
						int y = x;
						for( ; y && !nxt[o][y]; y = fail[y]);
						y = nxt[o][y];
						mod_inc(f[cur][j | msk[y]][y], f[pre][j][x]);
					}
	}
	int ans = 0;
	for(int i = 0; i <= tot; ++i) {
		int adt = 0;
		for(int x = i, y = i; x; x = fa[x])
			for(int o = 0; o < 2; ++o)
				if(nxt[o][fa[x]] != x) {
					for( ; y && !nxt[o][y]; y = fail[y]);
					y = nxt[o][y];
					adt |= msk[y];
				}
		for(int j = 0; j < 1 << n; ++j)
			if((j | adt) == (1 << n) - 1)
				mod_inc(ans, f[cur][j][i]);
	}
	printf("%d\n", ans);
	return 0;
}
