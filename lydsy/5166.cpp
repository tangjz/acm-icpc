#include <bits/stdc++.h>
using namespace std;
const int maxn = 101;
const double eps = 1e-9;
int n, r;
pair<double, double> seg[maxn];
int sgn(double x) {
	return (x > eps) - (x < -eps);
}
bool cmp(pair<double, double> const &u, pair<double, double> const &v) {
	int tmp = sgn(u.first - v.first);
	return tmp > 0 || (!tmp && sgn(u.second - v.second) < 0);
}
int main() {
	scanf("%d%d", &n, &r);
	for(int i = 0; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		double dt = sqrtl(r * r - y * y);
		seg[i] = make_pair(x - dt, x + dt);
	}
	sort(seg, seg + n, cmp);
	int tp = n;
	n = 0;
	for(int i = 0; i < tp; ++i)
		if(!(n && sgn(seg[n - 1].first - seg[i].first) >= 0 && sgn(seg[n - 1].second - seg[i].second) <= 0))
			seg[n++] = seg[i];
	sort(seg, seg + n);
	tp = n;
	n = 0;
	for(int i = 0; i < tp; ++i)
		if(!(n && sgn(seg[n - 1].second - seg[i].first) >= 0))
			seg[n++] = seg[i];
	printf("%d\n", n);
	return 0;
}
