#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxv = (int)1e9;
const LL INF = 3LL * maxv;
int n, m, mx, a[maxn], tot, ord[maxn], rnk[maxn], pL[maxn], pR[maxn];
LL ans;
bool cmp(int const &x, int const &y) {
	int dx = a[x + 1] - a[x];
	int dy = a[y + 1] - a[y];
	return dx < dy || (dx == dy && x < y);
}
LL solve() {
	if(m == n || mx == n - 1 || m > 1 && !mx)
		return INF;
	int adt = max(mx - (m - 1), 0);
	tot = 0;
	for(int i = m + 1; i < n; ++i)
		ord[++tot] = i;
	sort(ord + 1, ord + tot + 1, cmp);
	ord[0] = 0;
	pR[0] = ord[1];
	ord[tot + 1] = n;
	pL[n] = ord[tot];
	for(int i = 1; i <= tot; ++i) {
		rnk[ord[i]] = i;
		pL[ord[i]] = ord[i - 1];
		pR[ord[i]] = ord[i + 1];
	}
	LL ret = a[n] - a[n - adt];
	int pos = 0, sum = 0;
	for(int i = 0; i < adt; ++i) {
		pos = pR[pos];
		sum += a[pos + 1] - a[pos];
	}
	for(int i = 0; i < adt; ++i) {
		ret = min(ret, (LL)(a[n] - a[n - i]) + sum + sum);
		int j = n - 1 - i;
		pL[pR[j]] = pL[j];
		pR[pL[j]] = pR[j];
		if(rnk[j] <= rnk[pos]) {
			sum -= a[j + 1] - a[j];
			if(j == pos)
				pos = pL[pos];
		} else {
			sum -= a[pos + 1] - a[pos];
			pos = pL[pos];
		}
	}
	ret += a[n] - a[1] + a[m] - a[1];
	return ret;
}
int main() {
	scanf("%d%d%d", &n, &mx, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	ans = solve();
	for(int i = 1; i <= n; ++i)
		a[i] = maxv - a[i];
	reverse(a + 1, a + n + 1);
	mx = n - 1 - mx;
	m = n - m + 1;
	ans = min(ans, solve());
	printf("%lld\n", ans < INF ? ans : -1);
	return 0;
}
