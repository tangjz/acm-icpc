#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)1e5 + 1, maxm = maxn * 90 + 1;

int ptot;
struct Node {
	int cnt, lch, rch;
} pool[maxm];

inline int newNode(int lch, int rch) {
	pool[ptot] = (Node){pool[lch].cnt + pool[rch].cnt, lch, rch};
	return ptot++;
}

void solve() {
	int n, m = 0, mx = 0;
	LL ans = 0;
	static int a[maxn], rt[maxn], stk[maxn];
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		for( ; (1 << mx) <= a[i]; ++mx);
	}
	ptot = 1;
	for(int i = 0; i < n; ++i) {
		int cur = rt[i] = newNode(0, 0);
		for(int j = mx - 1; j >= 0; --j) {
			int o = (a[i] >> j) & 1, nxt = newNode(0, 0);
			++pool[cur].cnt;
			(o & 1 ? pool[cur].rch : pool[cur].lch) = nxt;
			cur = nxt;
		}
		++pool[cur].cnt;
	}
	function<void(int, int, int, int)> checkNode = [&](int dep, int x, int p, int v) {
		if(!x || !p || dep == -1)
			return;
		int o = (v >> dep) & 1;
		if(!o)
			ans += (LL)pool[pool[x].lch].cnt * pool[pool[p].rch].cnt + (LL)pool[pool[x].rch].cnt * pool[pool[p].lch].cnt;
		checkNode(dep - 1, pool[x].lch, o ? pool[p].rch : pool[p].lch, v);
		checkNode(dep - 1, pool[x].rch, o ? pool[p].lch : pool[p].rch, v);
	};
	function<int(int, int, int, int, int)> mergeNode = [&](int dep, int x, int y, int p, int v) {
		if(!x)
			return y;
		if(!y) {
			checkNode(dep, x, p, v);
			return x;
		}
		if(dep == -1) {
			int rt = newNode(0, 0);
			pool[rt].cnt = pool[x].cnt + pool[y].cnt;
			return rt;
		}
		int o = (v >> dep) & 1;
		if(!o && p)
			ans += (LL)pool[pool[x].lch].cnt * pool[pool[p].rch].cnt + (LL)pool[pool[x].rch].cnt * pool[pool[p].lch].cnt;
		return newNode(
			mergeNode(dep - 1, pool[x].lch, pool[y].lch, o ? pool[p].rch : pool[p].lch, v),
			mergeNode(dep - 1, pool[x].rch, pool[y].rch, o ? pool[p].lch : pool[p].rch, v)
		);
	};
	auto mergeRoot = [&](int u, int v) { // u <- v
		int x = rt[u], y = rt[v];
		if(pool[x].cnt > pool[y].cnt)
			swap(x, y);
		rt[u] = mergeNode(mx - 1, x, y, y, a[u]);
	};
	for(int i = 0; i < n; ++i) {
		int las = -1;
		for( ; m > 0 && a[stk[m - 1]] < a[i]; --m) {
			if(las != -1)
				mergeRoot(stk[m - 1], las);
			las = stk[m - 1];
		}
		if(las != -1)
			mergeRoot(i, las);
		stk[m++] = i;
	}
	for(int las = -1; m > 0; --m) {
		if(las != -1)
			mergeRoot(stk[m - 1], las);
		las = stk[m - 1];
	}
	printf("%lld\n", ans);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}
