#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double DB;
const int maxn = (int)1e5 + 1;
int t, n, m, tot;
struct Point {
	int x, y;
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	LL det(Point const &t) const {
		return (LL)x * t.y - (LL)y * t.x;
	}
} p[maxn], q[maxn];
struct Event {
	int typ, x;
	DB a, b;
	bool operator < (Event const &t) const {
		return x < t.x;
	}
} eve[maxn << 2 | 1];
void readPolygon(int &n, Point p[], int &low, int &upp, int typ) {
	LL area = 0;
	scanf("%d%d%d", &n, &p[0].x, &p[0].y);
	low = upp = p[0].x;
	for(int i = 1; i < n; ++i) {
		scanf("%d%d", &p[i].x, &p[i].y);
		low = min(low, p[i].x);
		upp = max(upp, p[i].x);
		area += p[i - 1].det(p[i]);
	}
	area += p[n - 1].det(p[0]);
	if(area < 0)
		reverse(p, p + n);
	for(int i = 0; i < n; ++i) {
		int j = i ? i - 1 : n - 1;
		if(p[i].x == p[j].x)
			continue;
		DB a = (DB)(p[i].y - p[j].y) / (p[i].x - p[j].x), b = p[i].y - a * p[i].x;
		eve[tot++] = (Event){typ, p[i].x, a, b};
		eve[tot++] = (Event){typ, p[j].x, -a, -b};
	}
}
int main() {
	scanf("%d", &t);
	while(t--) {
		int pxLow, pxUpp, qxLow, qxUpp;
		tot = 0;
		readPolygon(n, p, pxLow, pxUpp, 0);
		readPolygon(m, q, qxLow, qxUpp, 1);
		if(pxLow != qxLow || pxUpp != qxUpp) {
			puts("-1");
			continue;
		}
		sort(eve, eve + tot);
		DB a = 0, b = 0, c = 0, d = 0, ans = 0;
		for(int i = 0; i < tot; ) {
			int cur = eve[i].x;
			for( ; i < tot && eve[i].x == cur; ++i)
				if(!eve[i].typ) {
					a += eve[i].a;
					b += eve[i].b;
				} else {
					c += eve[i].a;
					d += eve[i].b;
				}
			if(i < tot) {
				int nxt = eve[i].x;
				DB coeff3 = a * c / 3, coeff2 = (a * d + b * c) / 2, coeff1 = b * d;
				ans += ((coeff3 * nxt + coeff2) * nxt + coeff1) * nxt;
				ans -= ((coeff3 * cur + coeff2) * cur + coeff1) * cur;
			}
		}
		printf("%.20f\n", (double)ans);
	}
	return 0;
}