#include <stdio.h>
#include <cstring>
const int maxn = (int)1e6 + 1, maxn2 = maxn << 1 | 1, maxc = 27, maxd = 21;
int cnt, rt, last, dep[maxn2], par[maxn2], son[maxn2][maxc], f[maxn2];
int newNode(int depth) {
	dep[++cnt] = depth;
	memset(son[cnt], 0, sizeof son[0]);
	return cnt;
}
void append(int ch) {
	if(!son[last][ch]) {
		int cur = newNode(dep[last] + 1), u = last;
		for( ; u && !son[u][ch]; son[u][ch] = cur, u = par[u]);
		if(!u) {
			par[cur] = rt;
		} else {
			int v = son[u][ch];
			if(dep[v] == dep[u] + 1) {
				par[cur] = v;
			} else {
				int adt = newNode(dep[u] + 1);
				memcpy(son[adt], son[v], sizeof son[0]);
				par[adt] = par[v];
				par[cur] = par[v] = adt;
				for( ; u && son[u][ch] == v; son[u][ch] = adt, u = par[u]);
			}
		}
		last = cur;
	} else {
		int u = last, v = son[u][ch];
		if(dep[v] == dep[u] + 1) {
			last = v;
		} else {
			int adt = newNode(dep[u] + 1);
			memcpy(son[adt], son[v], sizeof son[0]);
			par[adt] = par[v];
			par[v] = adt;
			for( ; u && son[u][ch] == v; son[u][ch] = adt, u = par[u]);
			last = adt;
		}
	}
	!f[last] && (++f[last]);
}
const int maxm = (int)1e5 + 1;
int m, pos[maxn], *tail = pos, *sta[maxm];
char buf[maxn];
int mx, lnk[maxn2], st[maxd][maxn2];
struct Edge {
	int nxt, v;
} e[maxn2];
void dfs(int u) {
	for(int it = lnk[u]; it; it = e[it].nxt) {
		int v = e[it].v;
		st[0][v] = u;
		for(int i = 1; st[i - 1][v]; mx < ++i && (mx = i))
			st[i][v] = st[i - 1][st[i - 1][v]]; 
		dfs(v);
		f[u] += f[v];
	}
}
int main() {
	rt = newNode(0);
	scanf("%d", &m);
	for(int i = 0; i < m; ++i) {
		scanf("%s", buf);
		last = rt;
		sta[i] = tail;
		for(int j = 0; buf[j]; ++j) {
			append(buf[j] - 'a');
			*(tail++) = last;
		}
	}
	for(int i = 2; i <= cnt; ++i) {
		e[i] = (Edge){lnk[par[i]], i};
		lnk[par[i]] = i;
	}
	dfs(rt);
	scanf("%d", &m);
	while(m--) {
		int i, L, R;
		scanf("%d%d%d", &i, &L, &R);
		int cur = sta[i - 1][R - 1], len = R - L + 1;
		for(int i = mx - 1; i >= 0; --i)
			if(dep[st[i][cur]] >= len)
				cur = st[i][cur];
		printf("%d\n", f[cur]);
	}
	return 0;
}
