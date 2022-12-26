#include <bits/stdc++.h>
typedef long long LL;
const int maxn = (int)6e7 + 1, maxm = (int)2e4 + 1;
int tot, pr[maxn >> 12 | 1], d[maxn], t, m;
LL n, fct[maxm], f[maxn], ff[maxm], ans;
bool vis[maxm];
inline LL sum2(LL n) {
	return n & 1 ? n * ((n + 1) >> 1) : (n >> 1) * (n + 1);
}
inline LL F(LL n) {
	if(n < maxn)
		return f[n];
	int idx = std::lower_bound(fct, fct + m, n) - fct;
	LL &ret = ff[idx];
	if(vis[idx])
		return ret;
	vis[idx] = 1;
	ret = sum2(n);
	for(LL i = 2, j, k, pre = 1, cur; i <= n; i = j + 1, pre = cur) {
		k = n / i;
		j = n / k;
		cur = j;
		ret -= (cur - pre) * F(k);
	}
	return ret;
}
int main() {
	d[1] = f[1] = 1;
	for(int i = 2; i < maxn; ++i) {
		if(!d[i]) {
			pr[tot++] = d[i] = i;
			f[i] = i - 1;
		}
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j]) {
				f[k] = f[i] * pr[j];
				break;
			}
			f[k] = f[i] * (pr[j] - 1);
		}
		f[i] += f[i - 1];
	}
	scanf("%d", &t);
	while(t--) {
		m = 0;
		scanf("%lld", &n);
		for(LL i = maxn, j, k; i <= n; i = j + 1) {
			k = n / i;
			j = n / k;
			fct[m++] = j;
		}
		memset(vis, 0, m * sizeof(bool));
		ans = -sum2(n);
		for(LL i = 1, j, k, pre = 0, cur; i <= n; i = j + 1, pre = cur) {
			k = n / i;
			j = n / k;
			cur = sum2(j);
			ans += (cur - pre) * F(k);
		}
		printf("%llu\n", ans);
	}
	return 0;
}
