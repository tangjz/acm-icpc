#include <bits/stdc++.h>
typedef long long LL;
const int maxn = (int)5e7 + 1;
int tot, pr[maxn >> 12 | 1], d[maxn], mu[maxn], f[maxn], g[maxn];
LL n, ans;
inline int iSqrt(LL n) {
	int x = (int)floor(sqrt(n));
	LL y = (LL)x * x;
	for( ; y > n; --x, y -= x << 1 | 1);
	for( ; y + (x << 1 | 1) <= n; y += x << 1 | 1, ++x);
	return x;
}
LL F(LL n) {
	if(n < maxn)
		return f[n];
	LL ret = 0;
	for(LL i = 1, x = 1; x + (i << 2) <= n; x += i << 3, ++i) // x=(2i-1)^2
		ret += ((iSqrt((n << 1) - x) + 1) >> 1) - i;
	return ret;
}
LL G(LL n) {
	if(n < maxn)
		return g[n];
	LL ret = 0;
	for(LL i = 1, x = 1; x <= n; x += (i + 1) << 2, i += 2) // x=i^2, i is odd
		if(mu[i])
			mu[i] > 0 ? ret += n / x : ret -= n / x;
	return ret;
}
void dfs(int x, int y, int z) {
	register int k, t;
	for(t = z, k = z << 3; t < maxn; t += k, k += z << 3) // t=i^2*z, i is odd
		++f[t];
	if((t = 2 * x - 2 * y + 3 * z) < maxn)
		dfs(x - 2 * y + 2 * z, 2 * x - y + 2 * z, t);
	if((t = 2 * x + 2 * y + 3 * z) < maxn)
		dfs(x + 2 * y + 2 * z, 2 * x + y + 2 * z, t);
	if((t = 2 * y + 3 * z - 2 * x) < maxn)
		dfs(2 * y + 2 * z - x, y + 2 * z - 2 * x, t);
}
int main() {
	dfs(3, 4, 5);
	d[1] = mu[1] = g[1] = 1;
	for(int i = 2; i < maxn; ++i) {
		if(!d[i]) {
			pr[tot++] = d[i] = i;
			mu[i] = -1;
		}
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
			mu[k] = -mu[i];
		}
		f[i] += f[i - 1];
		g[i] = g[i - 1] + (mu[i] != 0);
	}
	for(int i = 4; i < maxn; ++i)
		g[i] += g[i >> 2];
	scanf("%lld", &n);
	for(LL i = 1, j, k, pre = 0, cur; i <= n; i = j + 1, pre = cur) {
		k = n / i;
		j = n / k;
		cur = F(j);
		ans += (cur - pre) * G(k);
	}
	printf("%lld\n", ans);
	return 0;
}