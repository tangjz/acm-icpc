#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 301, maxm = 90001;
int t, n, m;
struct Point {
	int x, y;
	bool operator == (Point const &t) const {
		return x == t.x && y == t.y;
	}
	LL det(Point const &t) const {
		return (LL)x * t.y - (LL)y * t.x;
	}
	LL dot(Point const &t) const {
		return (LL)x * t.x + (LL)y * t.y;
	}
	bool operator < (Point const &t) const {
		return det(t) > 0;
	}
} p[maxn], vec[maxm];
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d", &n);
		m = 0;
		vec[m++] = (Point){1, 0};
		vec[m++] = (Point){0, 1};
		for(int i = 0; i < n; ++i) {
			scanf("%d%d", &p[i].x, &p[i].y);
			for(int j = 0; j < i; ++j) {
				int dx = p[i].x - p[j].x;
				int dy = p[j].y - p[i].y;
				if(dx < 0 || (!dx && dy < 0)) {
					dx = -dx;
					dy = -dy;
				}
				if(dy < 0)
					continue;
				int com = __gcd(dx, dy);
				vec[m++] = (Point){dx / com, dy / com};
			}
		}
		sort(vec, vec + m);
		m = unique(vec, vec + m) - vec;
		printf("Case #%d: %d\n", Case, m - 1);
	}
	return 0;
}