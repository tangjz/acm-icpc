#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
#define x first
#define y second
const int maxn = (int)1e5 + 1, INF = 0x3f3f3f3f;
int n, a[maxn], m, in[maxn], out[maxn], seg[maxn << 1 | 1];
vector<int> e[maxn];
inline bool cmp(int const &u, int const &v) {
	int lft = a[u] ? a[u] : INF;
	int rht = a[v] ? a[v] : INF;
	return lft < rht || (lft == rht && u < v);
}
inline int seg_min(int u, int v) {
	return cmp(u, v) ? u : v;
}
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
void seg_init(int L, int R) {
	if(L == R)
		return;
	int M = (L + R) >> 1;
	seg_init(L, M);
	seg_init(M + 1, R);
	seg[seg_idx(L, R)] = seg_min(seg[seg_idx(L, M)], seg[seg_idx(M + 1, R)]);
}
int seg_que(int L, int R, int l, int r) {
	if(l <= L && R <= r)
		return seg[seg_idx(L, R)];
	int M = (L + R) >> 1, ret = 0;
	if(l <= M)
		ret = seg_min(ret, seg_que(L, M, l, r));
	if(r > M)
		ret = seg_min(ret, seg_que(M + 1, R, l, r));
	return ret;
}
void seg_upd(int L, int R, int x) {
	if(L == R)
		return;
	int M = (L + R) >> 1;
	if(x <= M)
		seg_upd(L, M, x);
	else
		seg_upd(M + 1, R, x);
	seg[seg_idx(L, R)] = seg_min(seg[seg_idx(L, M)], seg[seg_idx(M + 1, R)]);
}
void dfs(int u, int p) {
	in[u] = ++m;
	seg[seg_idx(m, m)] = u;
	for(int v : e[u])
		if(v != p)
			dfs(v, u);
	out[u] = m;
}
int main() {
	int t = 1;
	// scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		a[0] = 0;
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		for(int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		m = 0;
		dfs(1, -1);
		seg_init(1, n);
		scanf("%d", &m);
		while(m--) {
			int rt, dt;
			scanf("%d%d", &rt, &dt);
			int id = seg_que(1, n, in[rt], out[rt]);
			if(!a[id]) {
				puts("-1");
				continue;
			}
			printf("%d\n", id);
			a[id] = max(a[id] - dt, 0);
			seg_upd(1, n, in[id]);
		}
		for(int i = 1; i <= n; ++i)
			vector<int>().swap(e[i]);
	}
	return 0;
}