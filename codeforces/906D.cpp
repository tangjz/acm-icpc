#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxm = 61, maxp = 31623, INF = 0x3f3f3f3f;
int tot, pr[maxp], d[maxp], n, m, mod[maxm], a[maxn], q, val[maxm];
int mod_pow(int x, int k, int p) {
	int ret = p > 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % p)
		(k & 1) && (ret = (LL)ret * x % p);
	return ret;
}
int int_pow(int x, int k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = x * x)
		(k & 1) && (ret = ret * x);
	return ret;
}
int phi(int x) {
	int ret = x;
	for(int i = 0; pr[i] * pr[i] <= x; ++i)
		if(x % pr[i] == 0) {
			for( ; x % pr[i] == 0; x /= pr[i]);
			ret -= ret / pr[i];
		}
	if(x > 1)
		ret -= ret / x;
	return ret;
}
int main() {
	for(int i = 2; i < maxp; ++i) {
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxp; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	pr[tot] = maxp;
	scanf("%d%d", &n, mod + 0);
	for(m = 1; mod[m - 1] > 1; mod[m] = phi(mod[m - 1]), ++m);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	scanf("%d", &q);
	while(q--) {
		int L, R;
		scanf("%d%d", &L, &R);
		R = min(R, L + m - 1);
		bool chk = 0;
		int res = 1;
		for(int i = R - L; i >= 0; --i) {
			int ex = res + chk * mod[i + 1];
			if(pow(a[L + i], ex) < INF) {
				res = int_pow(a[L + i], ex);
				if(res >= mod[i]) {
					res %= mod[i];
					chk = 1;
				} else {
					chk = 0;
				}
			} else {
				res = mod_pow(a[L + i], ex, mod[i]);
				chk = 1;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
