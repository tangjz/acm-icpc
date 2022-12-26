#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxm = (int)5e5 + 1;
int t, n, m, a[maxn], pL[maxm], pR[maxm], ord[maxm];
pair<int, int> b[maxn];
LL bits[2][maxn], ans[maxm];
inline void bit_upd(int x, int v) {
	for(int v2 = x * v; x > 0; x -= x & -x) {
		bits[0][x] += v;
		bits[1][x] += v2;
	}
}
inline LL bit_que(int x) {
	LL ret[2] = {};
	for(int i = x; i <= n; i += i & -i) {
		ret[0] += bits[0][i];
		ret[1] += bits[1][i];
	}
	return ret[1] - (x - 1) * ret[0];
}
inline bool isSquare(int x) {
	int y = (int)sqrt(x);
	for( ; y * y <= x; ++y);
	for( ; y * y > x; --y);
	return y * y == x;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		for(int i = 1; i <= m; ++i) {
			scanf("%d%d", pL + i, pR + i);
			ord[i] = i;
		}
		sort(ord + 1, ord + m + 1, [&pR](int const &u, int const &v) {
			return pR[u] < pR[v];
		});
		memset(bits[0] + 1, 0, n * sizeof(LL));
		memset(bits[1] + 1, 0, n * sizeof(LL));
		for(int i = 1, j = 1, sz = 0; i <= n; ++i) {
			b[++sz] = make_pair(a[i], i);
			int tp = 0;
			for(int k = 1; k <= sz; ++k) {
				b[k].first &= a[i];
				if(!tp || b[tp].first < b[k].first)
					++tp;
				b[tp] = b[k];
			}
			sz = tp;
			for(int k = 1; k <= sz; ++k)
				if(isSquare(b[k].first)) {
					bit_upd(b[k].second, 1);
					bit_upd(b[k - 1].second, -1);
				}
			for( ; j <= m && pR[ord[j]] == i; ++j)
				ans[ord[j]] = bit_que(pL[ord[j]]);
		}
		for(int i = 1; i <= m; ++i)
			printf("%lld\n", ans[i]);
	}
	return 0;
}
