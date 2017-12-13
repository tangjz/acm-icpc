#include <bits/stdc++.h>
typedef long long LL;
const LL maxn = (LL)1e12 + 1;
const int maxv = (int)1e7 + 1, maxm = (int)1e5 + 1;
int tot, pr[maxv], d[maxv], c1[maxv], c3[maxv], m;
LL fct[maxm], val[maxm];
LL calc1(LL, int);
inline LL calc3(LL n, int k) {
	if(k <= 1)
		return (n + 1) >> 2;
	if(n <= pr[k - 1])
		return 0;
	if(n < maxv) {
		if(c1[n] + c3[n] + (n > 1) <= k)
			return 0;
		int x = (int)sqrt(n);
		if(c1[x] + c3[x] + (x > 1) <= k)
			return c3[n] - c3[pr[k - 1]];
	}
	return calc3(n, k - 1) - ((pr[k - 1] & 3) == 3 ? calc1(n / pr[k - 1], k - 1) : calc3(n / pr[k - 1], k - 1));
}
inline LL calc1(LL n, int k) {
	if(k <= 1)
		return (n + 3) >> 2;
	if(n <= pr[k - 1])
		return n > 0;
	if(n < maxv) {
		if(c1[n] + c3[n] + (n > 1) <= k)
			return n > 0;
		int x = (int)sqrt(n);
		if(c1[x] + c3[x] + (x > 1) <= k)
			return c1[n] - c1[pr[k - 1]] + (n > 0);
	}
	return calc1(n, k - 1) - ((pr[k - 1] & 3) == 1 ? calc1(n / pr[k - 1], k - 1) : calc3(n / pr[k - 1], k - 1));
}
inline LL calc1(LL n) {
	if(n < maxv)
		return c1[n];
	LL &ret = val[std::lower_bound(fct, fct + m, n) - fct];
	if(ret != -1)
		return ret;
	int x = (int)ceil(sqrtl(n)) + 1;
	return ret = calc1(n, c1[x] + c3[x] + (x > 1)) + c1[x] - (n > 0);
}
LL solve(LL n) {
	LL ret = 0;
	m = 0;
	for(LL i = maxv - 1, j, k; i < n; i = j) {
		k = n / (i + 1);
		j = n / k;
		fct[m] = j;
		val[m++] = -1;
	}
	for(int i = 1; (LL)i * i <= n; i += 2) {
		bool sp = 0;
		int cnt = 0;
		static int seq[11];
		for(int tmp = i; tmp > 1; ) {
			int pp = d[tmp], ee = 0;
			for( ; d[tmp] == pp; tmp /= pp, ++ee);
			if((pp & 3) == 1 && (ee & 1)) {
				seq[cnt++] = pp;
				sp ^= 1;
			}
		}
		for(LL j = (LL)i * i, k; j <= n; j <<= 1) {
			k = n / j;
			ret += calc1(k); // type1
			for(int o = 0; o < cnt && seq[o] <= k; ++o, --ret); // type1 forbidden
			ret += sp; // type2
		}
	}
	return ret;
}
int main() {
	int sz = 16 << 20; // 16 MB
	char *p = (char *)malloc(sz) + sz;
	__asm__("movq %0, %%rsp\n" :: "r"(p));
	for(int i = 2; i < maxv; ++i) {
		if(!d[i]) {
			pr[tot++] = d[i] = i;
			c1[i] += (i & 3) == 1;
			c3[i] += (i & 3) == 3;
		}
		for(int j = 0, k; (k = i * pr[j]) < maxv; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
		c1[i] += c1[i - 1];
		c3[i] += c3[i - 1];
	}
	pr[tot] = maxv;
	for(LL n; scanf("%lld", &n) == 1; printf("%lld\n", solve(n)));
	exit(0); // return 0;
}
