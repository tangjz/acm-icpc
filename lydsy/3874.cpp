#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 201;
int n;
pair<LL, LL> a[maxn];
LL m, dt;
LL calc(LL lim) {
	LL ret = 0, rem = m - lim * dt;
	for(int i = 0; i < n; ++i) {
		LL upp = a[i].first - (i ? a[i - 1].first : -1);
		if(upp <= m / lim) {
			upp *= lim;
		} else {
			upp = m + 1;
		}
		LL cnt = min(upp, rem / a[i].second);
		ret += cnt;
		rem -= cnt * a[i].second;
		if(cnt < upp)
			break;
	}
	return ret;
}
int main() {
	scanf("%lld%lld%d", &m, &dt, &n);
	for(int i = 0; i < n; ++i)
		scanf("%lld%lld", &a[i].second, &a[i].first);
	sort(a, a + n);
	int tp = 0;
	for(int i = 0; i < n; ++i) {
		for( ; tp && a[tp - 1].second >= a[i].second; --tp);
		a[tp++] = a[i];
	}
	n = tp;
	LL cL = 1, cR = m / dt;
	while(cR - cL >= 4) {
		LL step = (cR - cL) / 3;
		LL cML = cL + step, dML = calc(cML);
		LL cMR = cR - step, dMR = calc(cMR);
		if(dML < dMR) {
			cL = cML;
		} else {
			cR = cMR;
		}
	}
	LL ans;
	for(ans = 0; cL <= cR; ans = max(ans, calc(cL++)));
	printf("%lld\n", ans);
	return 0;
}