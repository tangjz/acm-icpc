#include <cstdio>
typedef long long LL;
const int maxn = 1001, mod = (int)1e9 + 7;
int fact[maxn], iact[maxn];
int main() {
	iact[1] = 1;
	for(int i = 2; i < maxn; ++i)
		iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
	fact[0] = iact[0] = 1;
	for(int i = 1; i < maxn; ++i) {
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	}
	int t, n, m;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		if(n < m) {
			n = n + m;
			m = n - m;
			n = n - m;
		}
		printf("%d\n", (int)((LL)fact[n] * iact[m] % mod * iact[n - m] % mod));
	}
	return 0;
}
