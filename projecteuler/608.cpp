#include <bits/stdc++.h>
typedef long long LL;
const int maxm = 201, mod = (int)1e9 + 7;
const LL maxn = (LL)1e12 + 1;
int m, tot, pr[maxm], d[maxm], cnt[maxm];
LL n;
int dfs(int dep, LL val) {
	int ret = 0;
	LL lim = n / val, tmp = val;
	for(LL i = 0, j, k; i < lim; i = j) {
		k = lim / (i + 1);
		j = lim / k;
		ret = (ret + (j - i) * k) % mod;
	}
	for(int i = 2; i <= m; ++i)
		for(cnt[i] = 1; tmp % i == 0; tmp /= i, --cnt[i]);
	for(int i = m; i >= 2; --i)
		if(d[i] < i) {
			cnt[d[i]] += cnt[i];
			cnt[i / d[i]] += cnt[i];
		} else if(cnt[i]) {
			ret = (LL)ret * (((cnt[i] + 1) * (cnt[i] + 2)) >> 1) % mod;
		}
	for(int i = dep; i < tot && pr[i] <= lim; ++i)
		(ret -= dfs(i + 1, val * pr[i])) < 0 && (ret += mod);
	return ret;
}
int main() {
	m = maxm - 1;
	n = maxn - 1;
	for(int i = 2; i <= m; ++i) {
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) <= m; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	printf("%d\n", dfs(0, 1));
	return 0;
}
