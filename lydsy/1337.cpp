#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const int maxn = (int)1e5 + 1;
const DB eps = 1e-12;
int n;
struct Point {
	DB x, y;
	void read() {
		scanf("%lf%lf", &x, &y);
	}
	Point operator + (Point const &t) const {
		return (Point){x + t.x, y + t.y};
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	DB len2() const {
		return x * x + y * y;
	}
	DB det(Point const &t) const {
		return x * t.y - y * t.x;
	}
} p[maxn], c;
DB r2;
inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}
inline Point middle(Point u, Point v) {
	return (Point){(u.x + v.x) / 2, (u.y + v.y) / 2};
}
inline Point excenter(Point u, Point v, Point w) {
	DB uL = u.len2(), vL = v.len2(), wL = w.len2();
	DB den = (u.det(v) + v.det(w) + w.det(u)) * 2;
	Point o = (Point){uL, u.y}, p = (Point){vL, v.y}, q = (Point){wL, w.y};
	DB num1 = o.det(p) + p.det(q) + q.det(o);
	o.y = u.x, p.y = v.x, q.y = w.x;
	DB num2 = o.det(p) + p.det(q) + q.det(o);
	return (Point){num1 / den, -num2 / den};
}
inline int rand15() {
	return rand() & 0x3FFF;
}
inline int rand30() {
	return rand15() << 15 | rand15();
}
int main() {
	srand(19260817);
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		p[i].read();
	for(int i = 0; i < n; ++i)
		swap(p[i], p[i + rand30() % (n - i)]);
	c = middle(p[1], p[0]);
	r2 = (p[1] - c).len2();
	for(int i = 2; i < n; ++i) {
		if(sgn((p[i] - c).len2() - r2) > 0) {
			c = middle(p[i], p[0]);
			r2 = (p[i] - c).len2();
			for(int j = 1; j < i; ++j)
				if(sgn((p[j] - c).len2() - r2) > 0) {
					c = middle(p[i], p[j]);
					r2 = (p[i] - c).len2();
					for(int k = 0; k < j; ++k)
						if(sgn((p[k] - c).len2() - r2) > 0) { // assert(sgn((p[j] - p[i]).det(p[k] - p[i])));
							c = excenter(p[i], p[j], p[k]);
							r2 = (p[i] - c).len2();
						}
				}
		}
	}
	printf("%.3f\n", (DB)sqrtl(r2));
	return 0;
}
