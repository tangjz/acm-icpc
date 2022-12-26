#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)5e5 + 1, INF = 0x3f3f3f3f;
int n;
LL m, x[maxn], c[maxn], s[maxn], ans;
int main() {
	scanf("%d%lld", &n, &m);
	m >>= 1;
	for(int i = 1; i <= n; ++i)
		scanf("%lld", x + i);
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", c + i);
		s[i] = s[i - 1] + c[i];
	}
	int L = 1, R = 1;
	LL cnt = c[1], cost = 0;
	for(int i = 1; i <= n; ++i) {
		for( ; L < i && cost > m; ++L) {
			cnt -= c[L];
			cost -= (x[i] - x[L]) * c[L];
		}
		for( ; R + 1 <= n; ++R) {
			LL adt = (x[R + 1] - x[i]) * c[R + 1];
			if(cost + adt > m)
				break;
			cnt += c[R + 1];
			cost += adt;
		}
		for( ; L < i && R + 1 <= n; ) {
			LL lft = x[i] - x[L], rht = x[R + 1] - x[i];
			if(lft < rht)
				break;
			cnt -= c[L];
			cost -= lft * c[L];
			++L;
			for( ; R + 1 <= n && lft >= rht; ) {
				LL adt = rht * c[R + 1];
				if(cost + adt > m)
					break;
				cnt += c[R + 1];
				cost += adt;
				++R;
				rht = x[R + 1] - x[i];
			}
		}
//		fprintf(stderr, "%d: [%d, %d]: %lld %lld\n", i, L, R, cnt, cost);
		LL lft = L > 1 ? x[i] - x[L - 1] : INF, lc = L > 1 ? c[L - 1] : -1;
		LL rht = R + 1 <= n ? x[R + 1] - x[i] : INF, rc = R + 1 <= n ? c[R + 1] : -1;
		LL ctr = cnt, rem = m - cost;
		if(lft <= rht && lft < INF) {
			LL tmp = min(lc, rem / lft);
			ctr += tmp;
			lc -= tmp;
			rem -= lft * tmp;
		}
		if(lft >= rht && rht < INF) {
			LL tmp = min(rc, rem / rht);
			ctr += tmp;
			rc -= tmp;
			rem -= rht * tmp;
		}
		if(lft >= rht && lft < INF) {
			LL tmp = min(lc, rem / lft);
			ctr += tmp;
			lc -= tmp;
			rem -= lft * tmp;
		}
		if(lft <= rht && rht < INF) {
			LL tmp = min(rc, rem / rht);
			ctr += tmp;
			rc -= tmp;
			rem -= rht * tmp;
		}
		ans = max(ans, ctr);
		if(i + 1 <= n) {
			cost += (s[i] - s[L - 1]) * (x[i + 1] - x[i]);
			cost -= (s[R] - s[i]) * (x[i + 1] - x[i]);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
