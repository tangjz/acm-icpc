#include <cstdio>
typedef long long LL;
const int maxn = 200001, mod = 1000000007;
int iact[maxn], fact[maxn];
int n, a[maxn], ans;
inline int C(int n, int m) {
	return (LL)fact[n] * iact[m] % mod * iact[n - m] % mod;
}
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	iact[1] = 1;
	for(int i = 2; i <= n; ++i)
		iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
	fact[0] = iact[0] = 1;
	for(int i = 1; i <= n; ++i) {
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	}
	if(n & 1) {
		if(n & 2) {
			int m = n >> 1;
			for(int i = 0; i < m; ++i)
				ans = (ans + (LL)C(m - 1, i) * a[i << 1 | 1]) % mod;
			(ans <<= 1) >= mod && (ans -= mod);
			for(int i = 0; i < m; ++i)
				ans = (ans + (LL)C(m - 1, i) * (a[i << 1] - a[(i + 1) << 1])) % mod;
			if(ans < 0)
				ans += mod;
		} else {
			int m = (n + 1) >> 1;
			for(int i = 0; i < m; ++i)
				ans = (ans + (LL)C(m - 1, i) * a[i << 1]) % mod;
		}
	} else {
		int m = n >> 1;
		for(int i = 0; i < m; ++i)
			ans = (ans + (LL)C(m - 1, i) * a[i << 1]) % mod;
		if(m & 1) {
			for(int i = 0; i < m; ++i)
				ans = (ans + (LL)C(m - 1, i) * a[i << 1 | 1]) % mod;
		} else {
			for(int i = 0; i < m; ++i)
				ans = (ans - (LL)C(m - 1, i) * a[i << 1 | 1]) % mod;
			if(ans < 0)
				ans += mod;
		}
	}
	printf("%d\n", ans);
	return 0;
}
