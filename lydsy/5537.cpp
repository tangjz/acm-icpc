#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)3e5 + 1;
int n, m, p, inv[maxn], fct[maxn], ifct[maxn], pw1[maxn], pw2[maxn];
inline int mod_inv(int x) {
	return x <= n ? inv[x] : p - (int)(p / x * (LL)mod_inv(p % x) % p);
}
int main() {
	scanf("%d%d%d", &n, &m, &p);
	pw1[0] = pw2[0] = inv[1] = 1;
	pw1[1] = m;
	pw2[1] = 1 - m + p;
	for(int i = 2; i <= n; ++i) {
		pw1[i] = (LL)pw1[i - 1] * pw1[1] % p;
		pw2[i] = (LL)pw2[i - 1] * pw2[1] % p;
		inv[i] = p - (int)(p / i * (LL)mod_inv(p % i) % p);
	}
	fct[0] = ifct[0] = 1;
	for(int i = 1; i <= n; ++i) {
		fct[i] = (LL)fct[i - 1] * i % p;
		ifct[i] = (LL)ifct[i - 1] * inv[i] % p;
	}
	int ans = (LL)n * pw1[n] % p, ivs = mod_inv(m - 1);
	for(int i = 1; i <= n; ++i)
		for(int j = n, k = 0; j >= 0; j -= i, ++k) {
			int prd = (LL)fct[j + k] * ifct[j] % p * ifct[k] % p * pw1[j] % p * pw2[k] % p;
			if(k > 0)
				prd = prd * (1 + (LL)k * inv[j + k] % p * ivs % p) % p;
			(ans -= prd) < 0 && (ans += p);
		}
	printf("%d\n", ans);
	return 0;
}
