#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1, mod = (int)1e9 + 7, inv2 = (mod + 1) >> 1;
int f[maxn];
int s(LL n) {
	int res = 0;
	for(LL i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i);
		res = (res + n / i % mod * ((j - i + 1) % mod) % mod * ((i + j) % mod)) % mod;
	}
	res = (LL)res * inv2 % mod;
	return res;
}
int main() {
	f[1] = 1;
	for(int i = 1; i < maxn; ++i) {
		for(int j = i + i; j < maxn; j += i)
			f[j] -= f[i];
		f[i] *= i;
	}
	int T;
	scanf("%d", &T);
	while(T--) {
		LL n;
		scanf("%lld", &n);
		int ans = 0, lim = (int)ceil(sqrtl(n));
		for( ; (LL)lim * lim <= n; ++lim);
		for( ; (LL)lim * lim > n; --lim);
		LL las = 0;
		int val = 0;
		for(int i = 1; i <= lim; ++i) {
			if(!f[i])
				continue;
			LL cur = n / i / i;
			if(las != cur) {
				las = cur;
				val = s(cur);
			}
			if(f[i]) 
				ans = (ans + (LL)f[i] * val) % mod;
		}
		if(ans < 0)
			ans += mod;
		printf("%d\n", ans);
	}
	return 0;
}