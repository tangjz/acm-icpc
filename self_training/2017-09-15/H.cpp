#include <bits/stdc++.h>
using namespace std;
const int maxn = 21;
const double pi = acos(-1.0), eps = 1e-9;
int t, Case, n, m, f[maxn];
double x[maxn], y[maxn], cur;
inline int sgn(double x) {
	return (x > eps) - (x < -eps);
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d%d%lf", &Case, &n, &m, f + 0, &cur);
		cur = cur / 180 * pi;
		while(sgn(cur) <= 0)
			cur += pi;
		for(int i = 1; i <= n; ++i) {
			int idx;
			scanf("%d", &idx);
			scanf("%lf%lf", x + idx, y + idx);
		}
		for(int i = 0; i < m; ++i) { // f[i] -> f[i + 1]
			int p1, p2;
			double ang1 = pi * 2, ang2 = pi * 2;
			for(int j = 1; j <= n; ++j) {
				if(f[i] == j)
					continue;
				double tmp = atan2(y[j] - y[f[i]], x[j] - x[f[i]]);
				while(sgn(tmp) <= 0) // (-pi, pi] -> (0, pi]
					tmp += pi;
				if(sgn(tmp - cur) > 0 && sgn(tmp - ang1) < 0) {
					ang1 = tmp;
					p1 = j;
				}
				if(sgn(tmp - ang2) < 0) {
					ang2 = tmp;
					p2 = j;
				}
			}
			if(sgn(ang1 - pi) <= 0) {
				cur = ang1;
				f[i + 1] = p1;
			} else {
				cur = ang2;
				f[i + 1] = p2;
			}
		}
		printf("%d ", Case);
		for(int i = 1; i <= m; ++i)
			printf("%d%c", f[i], " \n"[i == m]);
	}
	return 0;
}
