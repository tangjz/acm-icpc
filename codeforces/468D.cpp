#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, rt, tot, sz[maxn], bel[maxn], in[maxn], out[maxn], seg[maxn << 1 | 1];
vector<pair<int, int> > e[maxn];
set<int> sp[maxn];
long long ans;
void dfs(int u, long long dis, int ori) {
	sz[u] = 1;
	ans += dis;
	bel[u] = ori;
	in[u] = ++tot;
	for(auto it : e[u]) {
		int v = it.first;
		int w = it.second;
		if(!in[v]) {
			dfs(v, dis + w, ori);
			sz[u] += sz[v];
		}
	}
	out[u] = tot;
}
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
void seg_upd(int L, int R, int x, int v) {
	int rt = seg_idx(L, R);
	if(L == R) {
		seg[rt] = v;
	} else {
		int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
		if(x <= M) {
			seg_upd(L, M, x, v);
		} else {
			seg_upd(M + 1, R, x, v);
		}
		seg[rt] = min(seg[lch], seg[rch]);
	}
}
int seg_que(int L, int R, int l, int r) {
	if(l <= L && R <= r)
		return seg[seg_idx(L, R)];
	int M = (L + R) >> 1, ret = n + 1;
	if(l <= M)
		ret = min(ret, seg_que(L, M, l, r));
	if(M < r)
		ret = min(ret, seg_que(M + 1, R, l, r));
	return ret;
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; ++i) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		e[u].push_back(make_pair(v, w));
		e[v].push_back(make_pair(u, w));
	}
	int *que = bel;
	tot = 0;
	memset(in + 1, 0, n * sizeof(int));
	que[++tot] = 1;
	in[1] = tot;
	for(int i = 1; i <= n; ++i) {
		int u = que[i];
		for(auto it : e[u]) {
			int v = it.first;
			if(!in[v]) {
				que[++tot] = v;
				in[v] = tot;
			}
		}
	}
	for(int i = n; i >= 1; --i) {
		int u = que[i], mx = 0;
		sz[u] = 1;
		for(auto it : e[u]) {
			int v = it.first;
			if(in[v] > in[u]) {
				sz[u] += sz[v];
				mx = max(mx, sz[v]);
			}
		}
		if(max(mx, n - sz[u]) << 1 <= n)
			rt = u;
	}
	tot = ans = 0;
	memset(in + 1, 0, n * sizeof(int));
	in[rt] = ++tot;
	bel[rt] = rt;
	for(auto it : e[rt]) {
		int v = it.first;
		int w = it.second;
		dfs(v, w, v);
		sp[sz[v] <<= 1].insert(v);
	}
	out[rt] = tot;
	printf("%lld\n", ans <<= 1);
	for(int i = 1; i <= n; ++i)
		seg_upd(1, n, in[i], i);
	for(int i = 1; i <= n; ++i) {
		int p = 0;
		for(auto u : sp[n - i + 1])
			if(u != bel[i])
				p = u;
		if(!p && i == rt)
			p = rt;
		if(p) {
			p = seg_que(1, n, in[p], out[p]);
		} else {
			p = n + 1;
			if(in[bel[i]] > 1)
				p = min(p, seg_que(1, n, 1, in[bel[i]] - 1));
			if(out[bel[i]] < n)
				p = min(p, seg_que(1, n, out[bel[i]] + 1, n));
		}
		printf("%d%c", p, " \n"[i == n]);
		seg_upd(1, n, in[p], n + 1);
		if(i != rt) {
			sp[sz[bel[i]]].erase(bel[i]);
			sp[--sz[bel[i]]].insert(bel[i]);
		}
		if(p != rt) {
			sp[sz[bel[p]]].erase(bel[p]);
			sp[--sz[bel[p]]].insert(bel[p]);
		}
	}
	return 0;
}
