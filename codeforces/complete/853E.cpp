#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxs = 21;
int n, m, q, stot, etot, que[maxn], rnk[maxn];
LL bit[maxn], ans[maxn];
struct Point {
	int x, y;
	void read() {
		scanf("%d%d", &x, &y);
	}
	bool operator < (Point const &t) const {
		return x < t.x || (x == t.x && y < t.y);
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	Point operator + (Point const &t) const {
		return (Point){x + t.x, y + t.y};
	}
	Point operator * (int const &t) const {
		return (Point){x * t, y * t};
	}
	LL det(Point const &t) const {
		return (LL)x * t.y - (LL)y * t.x;
	}
} stk[maxs], vec;
pair<Point, int> a[maxn], b[maxn];
Point p[maxn << 1 | 1];
struct Event {
	int typ, idx;
	LL dis;
	bool operator < (Event const &t) const {
		return dis < t.dis || (dis == t.dis && typ < t.typ);
	}
} eve[maxn << 2 | 1];
int main() {
	scanf("%d%d%d", &m, &n, &q);
	stk[stot++] = (Point){0, 0};
	while(m--) {
		vec.read();
		for(int i = 0; i < stot; ++i) {
			stk[stot + i] = stk[i] + vec;
			stk[i] = stk[i] - vec;
		}
		sort(stk, stk + stot + stot);
		int sz = 0;
		for(int i = 0; i < stot + stot; ++i) {
			for( ; sz > 1 && (stk[sz - 1] - stk[sz - 2]).det(stk[i] - stk[sz - 2]) <= 0; --sz);
			stk[sz++] = stk[i];
		}
		stot = sz;
	}
	stot -= stot > 1 && !(stk[stot - 1] - stk[stot - 2]).x;
	for(int i = 0; i < n; ++i) {
		a[i].first.read();
		scanf("%d", &a[i].second);
		que[i] = a[i].first.x;
	}
	sort(que, que + n);
	m = unique(que, que + n) - que;
	for(int i = 0; i < n; ++i)
		rnk[i] = lower_bound(que, que + m, a[i].first.x) - que + 1;
	for(int i = 0; i < q; ++i) {
		b[i].first.read();
		scanf("%d", &b[i].second);
	}
	for(int i = 0; i + 1 < stot; ++i) {
		vec = stk[i + 1] - stk[i];
		etot = 0;
		for(int j = 0; j < n; ++j)
			eve[etot++] = (Event){0, j, vec.det(a[j].first)};
		for(int j = 0; j < q; ++j) {
			p[j << 1] = b[j].first + stk[i] * b[j].second;
			eve[etot++] = (Event){-1, j << 1, vec.det(p[j << 1])};
			p[j << 1 | 1] = b[j].first - stk[i + 1] * b[j].second;
			eve[etot++] = (Event){1, j << 1 | 1, vec.det(p[j << 1 | 1])};
		}
		sort(eve, eve + etot);
		memset(bit + 1, 0, m * sizeof(LL));
		auto bit_upd = [&](int x, int v) {
			for( ; x <= m; x += x & -x)
				bit[x] += v;
		};
		auto bit_sum = [&](int x) {
			LL ret = 0;
			for( ; x > 0; x -= x & -x)
				ret += bit[x];
			return ret;
		};
		for(int j = 0; j < etot; ++j) {
			int idx = eve[j].idx;
			if(!eve[j].typ) {
				bit_upd(rnk[idx], a[idx].second);
			} else {
				Point lft = p[idx], rht = lft + vec * b[idx >> 1].second;
				lft.x += eve[j].typ < 0 && i > 0 || eve[j].typ > 0 && i + 2 < stot;
				int L = lower_bound(que, que + m, lft.x) - que + 1;
				int R = upper_bound(que, que + m, rht.x) - que;
				LL las = ans[idx >> 1];
				ans[idx >> 1] += eve[j].typ * (bit_sum(R) - bit_sum(L - 1));
				las = ans[idx >> 1] - las;
			}
		}
	}
	for(int i = 0; i < q; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}