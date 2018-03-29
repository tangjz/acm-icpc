#include <bits/stdc++.h>
typedef long long LL;
const int maxn = (int)1e6 + 1, mod = 2017, maxm = 101;
int tot, pr[maxn], d[maxn], sq, cnt, p[maxm];
LL n, pp[maxm];
inline LL sum2(LL x) {
	assert(x <= (int)1e9);
	return x * (x + 1) / 2;
}
inline bool isprime(LL x) {
	if(x < maxn)
		return d[x] == x;
	for(int i = 0; pr[i] <= sq; ++i)
		if(x % pr[i] == 0)
			return 0;
	return 1;
}
int main() {
	for(int i = 2; i < maxn; ++i) {
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	pr[tot] = maxn;
	while(scanf("%lld", &n) == 1) {
		assert(n <= (LL)1e12);
		for(sq = 1; (LL)sq * sq <= n; ++sq);
		cnt = 0;
		for(int i = 0; pr[i] < sq; ++i) {
			LL val = pr[i], sum = (1 + val) % mod, lim = n / val;
			for( ; ; val *= pr[i], sum = (sum + val) % mod) {
				if(!sum) {
					p[cnt] = pr[i];
					pp[cnt++] = val;
				}
				if(val > lim)
					break;
			}
		}
		LL ans = 0;
		for(int i = 0; i < cnt; ++i) {
			LL lim = n / pp[i];
			ans += sum2(lim) * pp[i];
			if(p[i] <= lim)
				ans -= sum2(lim / p[i]) * p[i] * pp[i];
			for(int j = i + 1; j < cnt; ++j)
				if(pp[j] <= lim) {
					LL lim2 = lim / pp[j];
					ans -= sum2(lim2) * pp[j] * pp[i];
					assert(p[j] > lim2 && p[i] > lim2);
				}
		}
		for(LL i = (sq / mod + 1) * mod - 1; i <= n; i += mod)
			if(isprime(i)) {
				ans += sum2(n / i) * i;
				LL lim = n / i;
				for(int j = 0; j < cnt; ++j)
					if(pp[j] <= lim) {
						LL lim2 = lim / pp[j];
						ans -= sum2(lim2) * pp[j] * i;
						assert(p[j] > lim2);
					}
			}
		printf("%lld\n", ans);
	}
	return 0;
}
