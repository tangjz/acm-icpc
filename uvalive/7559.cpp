#include <cstdio>
typedef long long LL;
const int maxn = 5001, mod = (int)1e9 + 7, inv25 = (7LL * mod + 1) / 25;
int c[maxn], f[maxn], ans[maxn];
int main() {
	c[0] = 1;
	f[0] = 1 + inv25;
	for(int i = 1; i < maxn; ++i) {
		f[i] = 25LL * f[i - 1] % mod;
		for(int j = i; j >= 1; --j) {
			(c[j] += c[j - 1]) >= mod && (c[j] -= mod);
			ans[i] = (ans[i] + (LL)c[j] * c[j] % mod * f[j]) % mod;
		}
	}
	int t, n;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		printf("%d\n", ans[n]);
	}
	return 0;
}
