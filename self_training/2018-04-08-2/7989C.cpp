#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e5 + 1, INF = 0x3f3f3f3f;
int n, h, c[2];
pair<LL, LL> p[2][maxn];
LL ans;
int main() {
	scanf("%d%d", &n, &h);
	for(int i = 0; i < n; ++i) {
		int x, y;
		scanf("%d%d", &y, &x);
		int o = (y - x) & 1;
		p[o][c[o]++] = make_pair((LL)y - x, (LL)x);
	}
	for(int o = 0; o < 2; ++o) {
		sort(p[o], p[o] + c[o]);
		for(int i = 0; i < c[o]; ++i) {
			LL base = p[o][i].first, dt = p[o][i].second;
			ans += (h - 1) * 2;
			int pL = lower_bound(p[o], p[o] + c[o], make_pair(base - (h - 1 - dt) * 2, (LL)-INF)) - p[o];
			int pR = lower_bound(p[o], p[o] + c[o], make_pair(base + dt * 2 + 1, (LL)-INF)) - p[o] - 1;
			ans -= pR - pL;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
