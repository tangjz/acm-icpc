#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const int maxn = (int)2e3 + 1;
const DB eps = 1e-9;
inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}
int n, r, m, f[maxn];
struct Point {
	DB x, y;
	int site() const {
		int s = sgn(x);
		return s < 0 || (!s && sgn(y) > 0);
	}
	DB det(Point const &t) const {
		return x * t.y - y * t.x;
	}
	bool operator < (Point const &t) const {
		int dif = site() - t.site();
		return dif < 0 || (!dif && sgn(det(t)) > 0);
	}
} pL[maxn], pR[maxn], que[maxn << 1 | 1];
pair<int, int> seg[maxn];
int main() {
	scanf("%d%d", &n, &r);
	for(int i = 0; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		int dis2 = x * x + y * y;
		DB delta = sqrtl(dis2 - r * r);
		que[i << 1] = pL[i] = (Point){(x * r + y * delta) / dis2, (y * r - x * delta) / dis2};
		que[i << 1 | 1] = pR[i] = (Point){(x * r - y * delta) / dis2, (y * r + x * delta) / dis2};
	}
	sort(que, que + (n << 1));
	for(int i = 0; i < n; ++i) {
		int &L = seg[i].first = lower_bound(que, que + (n << 1), pL[i]) - que;
		int &R = seg[i].second = lower_bound(que, que + (n << 1), pR[i]) - que;
		if(L > R)
			swap(L, R);
	}
	sort(seg, seg + n);
	int ans = 0;
	for(int i = 0; i + ans < n; ++i) {
		m = 0;
		for(int j = i; j < n && seg[j].first < seg[i].second; ++j) {
			if(seg[j].second < seg[i].second)
				continue;
			int k = lower_bound(f + 1, f + m + 1, seg[j].second) - f;
			f[k] = seg[j].second;
			if(m < k)
				m = k;
		}
		if(ans < m)
			ans = m;
	}
	printf("%d\n", ans);
	return 0;
}