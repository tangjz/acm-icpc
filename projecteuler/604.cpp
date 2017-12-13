#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 3000001;
int tot, pr[maxn], d[maxn], phi[maxn];
int main() {
	phi[1] = 1;
	for(int i = 2; i < maxn; ++i) {
		if(!d[i]) {
			pr[tot++] = d[i] = i;
			phi[i] = i - 1;
		}
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j]) {
				phi[k] = phi[i] * pr[j];
				break;
			}
			phi[k] = phi[i] * (pr[j] - 1);
		}
	}
	for(LL n; scanf("%lld", &n) == 1; ) {
		LL ans = 1, sum = 0;
		for(int i = 2; ; ++i) {
			LL tmp = sum + (((LL)i * phi[i]) >> 1);
			if(tmp <= n) { // full
				ans += phi[i];
				sum = tmp;
			} else {
				tmp = (n - sum) / i; // pair
				ans += tmp << 1;
				sum += tmp * i;
				if(sum + ((i + 1) >> 1) <= n) { // single
					++ans;
					sum += (i + 1) >> 1;
				}
				break;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
