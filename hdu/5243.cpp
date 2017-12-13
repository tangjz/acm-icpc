#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const int maxn = 1001, maxm = 1000001;
const DB eps = 1e-12;
int t, n, m, tot;
inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}
struct Point {
	DB x, y;
	void init() {
		scanf("%lf%lf", &x, &y);
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	Point operator + (Point const &t) const {
		return (Point){x + t.x, y + t.y};
	}
	Point operator * (DB const &t) const {
		return (Point){x * t, y * t};
	}
	DB dot(Point const &t) const {
		return x * t.x + y * t.y;
	}
	DB det(Point const &t) const {
		return x * t.y - y * t.x;
	}
	DB len2() const {
		return dot(*this);
	}
	bool operator < (Point const &t) const {
		if(!sgn(y) && !sgn(t.y) && sgn(x) * sgn(t.x) <= 0)
			return sgn(x - t.x) > 0;
		if(!sgn(y) && sgn(x) >= 0 && sgn(t.y))
			return 1;
		if(!sgn(t.y) && sgn(t.x) >= 0 && sgn(y))
			return 0;
		if(sgn(y) * sgn(t.y) <= 0)
			return sgn(y - t.y) > 0;
		int tmp = sgn(det(t));
		return tmp > 0 || (!tmp && sgn(len2() - t.len2()) < 0);
	}
} a[maxn], b[maxm];
inline DB polyArea(int n, Point p[]) {
	DB area = p[n - 1].det(p[0]);
	for(int i = 1; i < n; ++i)
		area += p[i - 1].det(p[i]);
	return area * 0.5;
}
struct Line {
	Point p, v;
	bool operator < (Line const &t) const {
		return v < t.v;
	}
	bool onLeft(Point const &t) const {
		return sgn(v.det(t - p)) > 0;
	}
} c[maxm];
inline Point getLineIntersection(Line a, Line b) {
	DB coeff = b.v.det(a.p - b.p) / a.v.det(b.v);
	return a.p + a.v * coeff;
}
inline void halfPlaneIntersection(int n, Line a[], int &m, Point b[]) {
	int L = 0, R = 0;
	static Point p[maxm];
	static Line q[maxm];
	q[0] = a[0];
	for(int i = 1; i < n; ++i) {
		for( ; L < R && !a[i].onLeft(p[R - 1]); --R);
		for( ; L < R && !a[i].onLeft(p[L]); ++L);
		if(sgn(q[R].v.det(a[i].v)))
			q[++R] = a[i];
		else if(q[R].onLeft(a[i].p))
			q[R] = a[i];
		if(L < R)
			p[R - 1] = getLineIntersection(q[R - 1], q[R]);
	}
	for( ; L < R && !q[L].onLeft(p[R - 1]); --R);
	m = R - L + 1;
	if(m <= 2) {
		m = 0;
		return;
	}
	p[R] = getLineIntersection(q[R], q[L]);
	for(int i = 0; i < m; ++i)
		b[i] = p[L + i];
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		m = 0;
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			a[i].init();
		for(int i = 0, upp = n / 3 - 1; i < n; ++i) {
			tot = 0;
			for(int j = 0; j < n; ++j)
				if(i != j)
					b[tot++] = a[j] - a[i];
			sort(b, b + tot);
			for(int j = 0; j < tot; ++j)
				b[tot + j] = b[j];
			int cnt = tot;
			for(int j = 0, k = 0; j < tot; ++j, ++cnt) {
				for( ; k < tot + j && sgn(b[j].det(b[k])) >= 0; ++k, --cnt);
				if(cnt <= upp)
					c[m++] = (Line){a[i], b[j]};
			}
		}
		sort(c, c + m);
		halfPlaneIntersection(m, c, tot, b);
		printf("Case #%d: %.6f\n", Case, polyArea(tot, b));
	}
	return 0;
}
