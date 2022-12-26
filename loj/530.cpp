#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 101, maxp = 541 + 2, maxd = 61;
int t, n, pr[maxn], d[maxp];
LL pw[maxd], f[maxd], g[maxd], ans;
int main() {
	pr[0] = 1;
	for(int i = 1; i < maxn; ++i) {
		pr[i] = pr[i - 1];
		do {
			++pr[i];
			if(!d[pr[i]])
				d[pr[i]] = pr[i];
			for(int j = 1, k; (k = pr[i] * pr[j]) < maxp; ++j) {
				d[k] = pr[j];
				if(d[pr[i]] == pr[j])
					break;
			}
		} while(d[pr[i]] < pr[i]);
	}
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		ans = 1;
		for(int i = 1; i <= n; ++i) {
			int len;
			LL ex;
			scanf("%lld", &ex);
			pw[0] = 1;
			f[0] = g[0] = 0;
			for(len = 1; g[len - 1] < ex; ++len) {
				pw[len] = pw[len - 1] * pr[i];
				f[len] = f[len - 1] + pw[len - 1];
				g[len] = g[len - 1] + pw[len] - 1;
			}
			LL cur = 0;
			for(--len; len; --len) {
				if(g[len - 1] >= ex)
					continue;
				int dig = (ex - g[len - 1] - 1) / f[len] + 1;
				cur += dig * pw[len];
				ex -= dig * f[len];
			}
			if(ans < cur)
				ans = cur;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
