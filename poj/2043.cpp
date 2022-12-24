#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 101, maxv = (int)2e3 + 1;

struct Point {
	int x, y;
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	bool operator < (Point const &t) const {
		return x < t.x || (x == t.x && y < t.y);
	}
};

struct Line {
	Point p, v;
	Line() {}
	Line(Point const &a, Point const &b) {
		p = a;
		v = b;
		if(v < p)
			swap(p, v);
		v = v - p;
	}
	double getY(int const &x) const {
		// assert(v.x > 0 && p.x <= x && x <= p.x + v.x);
		return p.y + v.y * (x - p.x) / (double)v.x;
	}
};

void solve() {
	for(int n; scanf("%d", &n) == 1 && n; ) {
		int ans = 0, xL = maxv, xR = -maxv;
		static double a[maxn];
		static Point p[maxn];
		static Line l[maxn];
		for(int i = 0; i < n; ++i) {
			scanf("%d%d", &p[i].x, &p[i].y);
			xL = min(xL, p[i].x);
			xR = max(xR, p[i].x);
		}
		for(int i = 0; i < n; ++i) {
			l[i] = Line(p[i], p[i ? i - 1 : n - 1]);
			if(l[i].v.x > 0)
				a[i] = l[i].getY(l[i].p.x);
		}
		for(int x = xL + 1; x <= xR; ++x) {
			int m = 0, yL, yR = -maxv;
			static Point seg[maxn];
			for(int i = 0; i < n; ++i)
				if(l[i].p.x < x && x <= l[i].p.x + l[i].v.x) {
					double u = a[i], v = a[i] = l[i].getY(x);
					if(v < u)
						swap(u, v);
					seg[m++] = (Point){(int)floor(u), (int)ceil(v)};
				}
			sort(seg, seg + m);
			for(int i = 0; i < m; i += 2) {
				yL = max(yR, seg[i].x);
				yR = max(seg[i].y, seg[i + 1].y);
				ans += yR - yL;
			}
		}
		printf("%d\n", ans);
	}
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
