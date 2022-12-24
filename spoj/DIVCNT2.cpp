#include <bits/stdc++.h>
typedef long long LL;
const int maxt = (int)1e4 + 1, maxn = (int)8e7 + 1;
int tot, pr[maxn >> 12 | 1], d[maxn], mu[maxn], e[maxn], f[maxn], g[maxn], t, nLim;
LL seq[maxt], ans;
LL F(LL n) {
	if(n < nLim)
		return f[n];
	LL ret = 0;
	for(LL i = 0, j, k; i < n; i = j) {
		k = n / (i + 1);
		j = n / k;
		ret += (j - i) * k;
	}
	return ret;
}
LL G(LL n) {
	if(n < nLim)
		return g[n];
	LL ret = 0;
	for(LL i = 1, x = 1; x <= n; x += i << 1 | 1, ++i) // x=i^2
		if(mu[i])
			mu[i] > 0 ? ret += n / x : ret -= n / x;
	return ret;
}
int main() {
	scanf("%d", &t);
	for(int i = 0; i < t; ++i) {
		scanf("%lld", seq + i);
		ans = std::max(ans, seq[i]);
	}
	nLim = (int)std::min((LL)maxn, ans + 1);
	d[1] = mu[1] = f[1] = g[1] = 1;
	for(int i = 2; i < nLim; ++i) {
		if(!d[i]) {
			pr[tot++] = d[i] = i;
			mu[i] = -1;
			e[i] = 1;
			f[i] = 2;
		}
		for(int j = 0, k; (k = i * pr[j]) < nLim; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j]) {
				e[k] = e[i] + 1;
				f[k] = f[i] + f[i] / e[k];
				break;
			}
			mu[k] = -mu[i];
			e[k] = 1;
			f[k] = f[i] << 1;
		}
		f[i] += f[i - 1];
		g[i] = g[i - 1] + (mu[i] != 0);
	}
	for(int tt = 0; tt < t; ++tt) {
		LL &n = seq[tt];
		ans = 0;
		for(LL i = 0, j, k, pre = 0, cur; i < n; i = j, pre = cur) {
			k = n / (i + 1);
			j = n / k;
			cur = F(j);
			ans += (cur - pre) * G(k);
		}
		printf("%lld\n", ans);
	}
	return 0;
}