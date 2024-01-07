#include <cstdio>
#include <vector>
#include <cstring>
typedef long long LL;
const int maxn = 301, mod = (int)1e9 + 7;
int n, m, fact[maxn], iact[maxn], ans;
int main() {
	scanf("%d%d", &n, &m);
	iact[1] = 1;
	for(int i = 2; i <= n || i <= m; ++i)
		iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
	fact[0] = iact[0] = 1;
	for(int i = 1; i <= n || i <= m; ++i) {
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	}
	for(int i = 1; i <= n && i <= m; ++i)
		ans = (ans + (LL)iact[i - 1] * iact[n - i] % mod * iact[m - i]) % mod;
	ans = (LL)ans * fact[n - 1] % mod * fact[m] % mod;
	printf("%d\n", ans);
	return 0;
}
