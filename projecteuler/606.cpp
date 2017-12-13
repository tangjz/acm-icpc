#include <cmath>
#include <cstdio>
#include <cstdlib>
typedef long long LL;
const int maxn = (int)1e7 + 1, mod = (int)1e9;
int tot, pr[maxn], d[maxn], c[maxn], s[maxn];
inline LL cub(LL x) {
	x %= mod;
	return x * x % mod * x % mod;
}
inline int sum3(LL n) {
	n %= mod;
	int ret = ((n * (n + 1)) >> 1) % mod;
	return (LL)ret * ret % mod;
}
int solve(LL n, int k) {
    if(!k)
        return sum3(n);
    if(n <= pr[k - 1])
        return n > 0;
    if(n < maxn) {
        if(c[n] <= k)
            return n > 0;
        if(c[(int)sqrt(n)] <= k)
        	return (s[n] - s[pr[k - 1]] + (n > 0)) % mod;
    }
    return (solve(n, k - 1) - (LL)cub(pr[k - 1]) * solve(n / pr[k - 1], k - 1)) % mod;
}
int main() {
    s[1] = 1;
    for(int i = 2; i < maxn; ++i) {
        if(!d[i])
            pr[tot++] = d[i] = i;
        for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
            d[k] = pr[j];
            if(d[i] == pr[j])
                break;
        }
        c[i] = c[i - 1] + (d[i] == i);
        s[i] = (s[i - 1] + (d[i] == i ? cub(i) : 0)) % mod;
    }
    LL n = (LL)1e12, pos = 0;
	int ans = 0, val = 0, adt = 1;
    for(int i = 0; (LL)pr[i] * pr[i] < n; ++i) {
    	LL lim = n / pr[i];
    	if(lim != pos) {
    		pos = lim;
    		int upp = (int)ceil(sqrt(lim)) + 1;
    		val = (solve(lim, c[upp]) + s[upp] - 1) % mod;
    	}
    	adt = (adt + cub(pr[i])) % mod;
    	ans = (ans + (LL)cub(pr[i]) * (val - adt)) % mod;
    }
    printf("%d\n", ans < 0 ? ans + mod : ans);
    return 0;
}
