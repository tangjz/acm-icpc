#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100001;
int n, m, ord[maxn], sz1, stk1[maxn << 1 | 1], sz2, stk2[maxn];
struct Point {
	int x, y;
	bool operator < (Point const &t) const {
		return x < t.x || (x == t.x && y < t.y);
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	LL det(Point const &t) const {
		return (LL)x * t.y - (LL)y * t.x;
	}
} p[maxn];
inline bool cmp(int const &u, int const &v) {
	return p[u] < p[v];
}
void convex_hull(int n, int ord[], int &m, int stk[]) {
	m = 0;
	for(int i = 0; i < n; ++i) {
		for( ; m > 1 && (p[stk[m - 1]] - p[stk[m - 2]]).det(p[ord[i]] - p[stk[m - 2]]) <= 0; --m);
		stk[m++] = ord[i];
	}
	for(int i = n - 2, t = m; i >= 0; --i) {
		for( ; m > t && (p[stk[m - 1]] - p[stk[m - 2]]).det(p[ord[i]] - p[stk[m - 2]]) <= 0; --m);
		stk[m++] = ord[i];
	}
	if(n > 1)
		--m;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i) {
		scanf("%d%d", &p[i].x, &p[i].y);
		ord[i] = i;
	}
	sort(ord, ord + m, cmp);
	convex_hull(m, ord, sz1, stk1);
	sort(ord, ord + n, cmp);
	convex_hull(n, ord, sz2, stk2);
	for(int i = 0; i < sz1; ++i)
		stk1[sz1 + i] = stk1[i];
	stk1[sz1 << 1] = stk1[0];
	stk1[sz1 << 1 | 1] = stk1[1];
	int L = 0, R = 0;
	LL ans = 0, area = 0;
	for( ; R < sz1; ++R)
		area += p[stk1[R]].det(p[stk1[R + 1]]);
	for( ; (p[stk1[R]] - p[stk2[0]]).det(p[stk1[R - 1]] - p[stk2[0]]) >= 0; --R)
		area -= p[stk1[R - 1]].det(p[stk1[R]]);
	for(int i = 0; i < sz2; ++i) {
		for( ; (p[stk1[L]] - p[stk2[i]]).det(p[stk1[L + 1]] - p[stk2[i]]) <= 0; ++L)
			area -= p[stk1[L]].det(p[stk1[L + 1]]);
		for( ; (p[stk1[R]] - p[stk2[i]]).det(p[stk1[R + 1]] - p[stk2[i]]) > 0; ++R)
			area += p[stk1[R]].det(p[stk1[R + 1]]);
		ans = max(ans, area + p[stk1[R]].det(p[stk2[i]]) + p[stk2[i]].det(p[stk1[L]]));
	}
	printf("%I64d.%c\n", ans >> 1, ans & 1 ? '5' : '0');
	return 0;
}
