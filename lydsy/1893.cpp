#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL maxn = 1LL << 32;
int main() {
	int t;
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		int n, m, q;
		scanf("%d%d%d", &n, &m, &q);
		LL nn = 0, prd = 1;
		for(int i = 1; i <= m && i <= q; ++i) {
			prd = prd * (m - i + 1) / i;
			nn += prd;
			if(nn >= maxn) {
				nn = -1;
				break;
			}
		}
		int mm;
		if(q == 1) {
			mm = n;
		} else if(q == 2) {
			mm = (int)floor((sqrtl(n * 8 + 1) - 1) * 0.5);
			for( ; mm * (mm + 1LL) / 2 >= n; --mm);
			for( ; mm * (mm + 1LL) / 2 < n; ++mm);
		} else if(q == 3) {
			mm = (int)floor(pow(n * 6, 1.0 / 3) + 0.5);
			for( ; mm * (mm * mm + 5LL) / 6 >= n; --mm);
			for( ; mm * (mm * mm + 5LL) / 6 < n; ++mm);
		} else {
			for(mm = 1; ; ++mm) {
				LL nn = 0, prd = 1;
				for(int i = 1; i <= mm && i <= q; ++i) {
					prd = prd * (mm - i + 1) / i;
					nn += prd;
					if(nn >= n)
						break;
				}
				if(nn >= n)
					break;
			}
		}
		int qq;
		for(qq = 1; ; ++qq) {
			LL nn = 0, prd = 1;
			for(int i = 1; i <= m && i <= qq; ++i) {
				prd = prd * (m - i + 1) / i;
				nn += prd;
				if(nn >= n)
					break;
			}
			if(nn >= n)
				break;
		}
		printf("Case #%d: %lld %d %d\n", Case, nn, mm, qq);
	}
	return 0;
}
