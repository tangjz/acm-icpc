#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)5e5 + 1;
int n, m, qtot, stot, que[maxn], bit[maxn], ans[maxn];
pair<int, int> a[maxn];
struct Query {
	int ref, x, y;
	bool operator < (Query const &t) const {
		return x < t.x;
	}
} seq[maxn << 2 | 1];
inline void addQuery(int ref, int x, int y) {
	if(x >= a[0].first && y >= 1)
		seq[stot++] = (Query){ref, x, y};
}
void upd(int x) {
	for( ; x <= qtot; x += x & -x)
		++bit[x];
}
int ask(int x) {
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i) {
		scanf("%d%d", &a[i].first, &a[i].second);
		que[i] = a[i].second;
	}
	sort(a, a + n);
	sort(que, que + n);
	qtot = unique(que, que + n) - que;
	for(int i = 0; i < m; ++i) {
		int xL, yL, xR, yR;
		scanf("%d%d%d%d", &xL, &yL, &xR, &yR);
		--xL;
		yL = lower_bound(que, que + qtot, yL) - que;
		yR = lower_bound(que, que + qtot, yR + 1) - que;
		addQuery(i + 1, xR, yR);
		addQuery(-i - 1, xL, yR);
		addQuery(-i - 1, xR, yL);
		addQuery(i + 1, xL, yL);
	}
	sort(seq, seq + stot);
	for(int i = 0, j = 0; i < stot; ++i) {
		for( ; j < n && a[j].first <= seq[i].x; ++j)
			upd(lower_bound(que, que + qtot, a[j].second) - que + 1);
		int &res = ans[abs(seq[i].ref)];
		if(seq[i].ref > 0) {
			res += ask(seq[i].y);
		} else {
			res -= ask(seq[i].y);
		}
	}
	for(int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}