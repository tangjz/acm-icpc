#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 101;
const double pi = acos(-1.0);
int n, m, ord[maxn], stk[maxn];
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
	LL det(Point const &t) const {
		return (LL)x * t.y - (LL)y * t.x;
	}
	LL dot(Point const &t) const {
		return (LL)x * t.x + (LL)y * t.y;
	}
	double len() const {
		return sqrt(dot(*this));
	}
} p[maxn];
double ans[maxn];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		p[i].read();
		ord[i] = i;
	}
	sort(ord, ord + n, [&](int const &u, int const &v) {
		return p[u] < p[v];
	});
	for(int i = 0; i < n; ++i) {
		int o = ord[i];
		for( ; m > 1 && (p[stk[m - 1]] - p[stk[m - 2]]).det(p[o] - p[stk[m - 2]]) <= 0; --m);
		stk[m++] = o;
	}
	for(int i = n - 2, tp = m; i >= 0; --i) {
		int o = ord[i];
		for( ; m > tp && (p[stk[m - 1]] - p[stk[m - 2]]).det(p[o] - p[stk[m - 2]]) <= 0; --m);
		stk[m++] = o;
	}
	--m;
	if(m == 2) {
		ans[stk[0]] = ans[stk[1]] = 0.5;
	} else {
		for(int i = 0; i < m; ++i) {
			int lft = stk[(m + i - 1) % m], mid = stk[i], rht = stk[(i + 1) % m];
			Point pre = p[mid] - p[lft], suf = p[rht] - p[mid];
			ans[mid] = acos(pre.dot(suf) / pre.len() / suf.len()) / pi / 2;
		}
	}
	for(int i = 0; i < n; ++i)
		printf("%.20f\n", ans[i]);
	return 0;
}
