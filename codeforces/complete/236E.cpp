#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6 + 1, maxc = 26;
int cnt, rt, last, dep[maxn << 1 | 1], par[maxn << 1 | 1], son[maxn << 1 | 1][maxc | 1], sz[maxn << 1 | 1], ord[maxn << 1 | 1];
int newNode(int depth) {
	dep[++cnt] = depth;
	memset(son[cnt], 0, sizeof son[0]);
	return cnt;
}
void append(int ch) {
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
	++sz[last];
}
int n, m, ctr[maxn];
char buf[maxn];
int main() {
	scanf("%s", buf);
	n = strlen(buf);
	cnt = 0;
	rt = last = newNode(0);
	for(int i = 0; i < n; ++i)
		append(buf[i] - 'a');
	for(int i = 1; i <= cnt; ++i)
		++ctr[dep[i]];
	for(int i = 1; i <= n; ++i)
		ctr[i] += ctr[i - 1];
	for(int i = cnt; i >= 1; --i)
		ord[ctr[dep[i]]--] = i;
	for(int i = cnt; i > 1; --i) {
		int u = ord[i];
		sz[par[u]] += sz[u];
	}
	memset(ctr + 1, 0, cnt * sizeof(int));
	scanf("%d", &m);
	for(int Case = 1; Case <= m; ++Case) {
		scanf("%s", buf);
		int len = strlen(buf), cur = rt, com = 0, ans = 0;
		for(int i = 0; i < len + len; ++i) {
			if(i >= len && com >= len) {
				for( ; cur && dep[par[cur]] >= len; cur = par[cur])
					com = dep[par[cur]];
				if(!cur) {
					cur = rt;
				} else if(ctr[cur] < Case) {
					ans += sz[cur];
					ctr[cur] = Case;
				}
			}
			int ch = buf[i < len ? i : i - len] - 'a';
			for( ; cur && !son[cur][ch]; cur = par[cur])
				com = dep[par[cur]];
			if(!cur) {
				cur = rt;
			} else {
				cur = son[cur][ch];
				++com;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
