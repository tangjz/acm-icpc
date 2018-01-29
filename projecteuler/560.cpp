#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e7 + 1, mod = (int)1e9 + 7;
int tot, pr[maxn], d[maxn], sg[maxn], mx, c[maxn];
int mod_pow(int x, int k) {
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
		(k & 1) && (ret = (LL)ret * x % mod);
	return ret;
}
int mod_add(int x, int y) {
	return (x += y) < mod ? x : x - mod;
}
int mod_sub(int x, int y) {
	return (x -= y) < 0 ? x + mod : x;
}
void FWT_iterate(int x[], int len, int dt) {
	for(int i = 0; i < len; i += dt << 1)
		for(int j = 0; j < dt; ++j) {
			int t = x[i + dt + j];
			x[i + dt + j] = mod_sub(x[i + j], t);
			x[i + j] = mod_add(x[i + j], t);
		}
}
void FWT(int x[], int len, int flag) {
	if(flag > 0) {
		for(int i = 1; i < len; i <<= 1)
			FWT_iterate(x, len, i);
	} else {
		for(int i = len >> 1; i > 0; i >>= 1)
			FWT_iterate(x, len, i);
		int inv_len = mod_pow(len, mod - 2);
		for(int i = 0; i < len; ++i)
			x[i] = (LL)x[i] * inv_len % mod;
	}
}
int main() {
	int n, m;
	while(scanf("%d%d", &n, &m) == 2) {
		tot = 0;
		memset(d, 0, sizeof d);
		memset(c, 0, sizeof c);
		sg[1] = c[1] = 1;
		mx = 1 << (n > 1);
		for(int i = 2; i < n; ++i) {
			if(!d[i]) {
				pr[tot++] = d[i] = i;
				sg[i] = i == 2 ? 0 : tot;
			} else {
				sg[i] = sg[d[i]];
			}
			for(int j = 0, k; (k = i * pr[j]) < n; ++j) {
				d[k] = pr[j];
				if(d[i] == pr[j])
					break;
			}
			for(++c[sg[i]]; mx <= sg[i]; mx <<= 1);
		}
		FWT(c, mx, 1);
		for(int i = 0; i < mx; ++i)
			c[i] = mod_pow(c[i], m);
		FWT(c, mx, -1);
		printf("%d\n", c[0]);
	}
	return 0;
}
