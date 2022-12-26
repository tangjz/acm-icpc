#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = (int)2e5 + 1;
struct Point {
	LL x, y;
	bool operator < (Point const &t) const {
		return x != t.x ? (x < t.x) : (y < t.y);
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	LL det(Point const &t) const {
		return x * t.y - y * t.x;
	}
} p[maxn];
int n, b[maxn], m, stk[maxn];
LL a[maxn], c[maxn];
int main() {
	scanf("%d", &n);
	int pos = 0;
	for(int i = 0; i < n; ++i) {
		scanf("%lld", a + i);
		if(a[pos] < a[i])
			pos = i;
	}
	for(int i = 0; i < n; ++i)
		scanf("%d", b + i);
	rotate(a, a + pos, a + n);
	rotate(b, b + pos, b + n);
	a[n] = a[0];
	for(int i = 0; i <= n; ++i) {
		if(i > 1)
			c[i] = (b[i - 1] + c[i - 1]) * 2 - c[i - 2];
		p[i] = (Point){i, a[i] - c[i]};
		for( ; m > 1 && (p[stk[m - 1]] - p[stk[m - 2]]).det(p[i] - p[stk[m - 1]]) > 0; --m);
		stk[m++] = i;
	}
	DB ans = 0;
	for(int i = 0, j = 0; i < n; ++i) {
		for( ; stk[j] < i; ++j);
		if(stk[j] == i) {
			ans += a[i];
		} else {
			ans += ((i - stk[j - 1]) * p[stk[j]].y + (stk[j] - i) * p[stk[j - 1]].y) / (DB)(stk[j] - stk[j - 1]) + c[i];
		}
	}
	printf("%.20f\n", ans / n);
	return 0;
}