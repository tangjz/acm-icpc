#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, mod = 30013;
int n, ord[maxn], m, que[maxn];
struct Trapezoid {
	int xL, xR, yL, yR;
	void read() {
		scanf("%d%d%d%d", &xL, &xR, &yL, &yR);
	}
	bool operator < (Trapezoid const &t) const {
		return xL < t.xL;
	}
} a[maxn];
inline bool cmp(int const &u, int const &v) {
	return a[u].xR < a[v].xR;
}
inline void mod_inc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
struct Info {
	int val, ways;
	void update(Info const &t) {
		if(val < t.val) {
			*this = t;
		} else if(val == t.val) {
			mod_inc(ways, t.ways);
		}
	}
} f[maxn], g[maxn], ans;
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		a[i].read();
		ord[i] = i;
		que[i] = a[i].yR;
	}
	sort(a, a + n);
	sort(ord, ord + n, cmp);
	sort(que, que + n);
	m = unique(que, que + n) - que;
	for(int i = 0, j = 0; i < n; ++i) {
		for( ; j < n && a[ord[j]].xR < a[i].xL; ++j) {
			int k = ord[j], x = lower_bound(que, que + m, a[k].yR) - que + 1;
			for( ; x <= m; x += x & -x)
				g[x].update(f[k]);
		}
		int x = lower_bound(que, que + m, a[i].yL) - que;
		f[i].ways = 1;
		for( ; x > 0; x -= x & -x)
			f[i].update(g[x]);
		++f[i].val;
		ans.update(f[i]);
	}
	printf("%d %d\n", ans.val, ans.ways);
	return 0;
}