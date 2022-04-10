#include <bits/stdc++.h>
using namespace std;

typedef long long i64;
typedef double f64;

const int maxv = (int)1e6 + 1;

struct Point {
	int x, y, z;
	void read() {
		scanf("%d%d%d", &x, &y, &z);
	}
	int dot(Point const &t) const {
		return x * t.x + y * t.y + z * t.z;
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y, z - t.z};
	}
	Point operator + (Point const &t) const {
		return (Point){x + t.x, y + t.y, z + t.z};
	}
};

void solve() {
	f64 ans = maxv + 1;
	i64 lenB2, k, v;
	int n, m, r1, r2;
	Point A, B, C, D;
	A.read();
	B.read();
	lenB2 = B.dot(B);
	scanf("%d%d", &r1, &n);
	while(n--) {
		C.read();
		scanf("%d%d", &r2, &m);
		C = C - A;
		k = B.dot(C);
		if(k > 0) {
			v = ((r1 + r2) * (r1 + r2) - C.dot(C)) * lenB2 + k * k;
			if(v >= 0)
				ans = min(ans, (f64)((k - sqrtl(v)) / lenB2));
		}
		while(m--) {
			D.read();
			D = D + C;
			k = B.dot(D);
			if(k > 0) {
				v = (r1 * r1 - D.dot(D)) * lenB2 + k * k;
				if(v >= 0)
					ans = min(ans, (f64)((k - sqrtl(v)) / lenB2));
			}
		}
	}
	printf("%.20f\n", ans < maxv ? ans : -1);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		// printf("%d\n", solve());
		solve();
	}
	return 0;
}