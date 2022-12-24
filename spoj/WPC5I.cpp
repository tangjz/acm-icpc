#include <bits/stdc++.h>
const int maxn = 46341;
int tot, pr[maxn], d[maxn], t, n, m;
long long ans;
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
	scanf("%d", &t);
	while(t--) {
		ans = 1;
		scanf("%d%d", &n, &m);
		for(int i = 0; i < tot; ++i) {
			int c1 = 0, c2 = 0;
			for( ; n % pr[i] == 0; n /= pr[i], ++c1);
			for( ; m % pr[i] == 0; m /= pr[i], ++c2);
			if(c1 != c2)
				for(int j = 0; j < c1 || j < c2; ++j)
					ans *= pr[i];
		}
		if(n != m) {
			ans *= n;
			ans *= m;
		}
		printf("%lld\n", ans);
	}
	return 0;
}