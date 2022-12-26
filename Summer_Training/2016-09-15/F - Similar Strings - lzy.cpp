#include <cstdio>

#define N 5000

constexpr int mod = 1000000007;

int T, n;
int a[N + 9];
int ff[N + 9], gg[N + 9], *f = ff, *g = gg, *h;
int ans[N + 9];

int main() {
	scanf("%d", &T);
	n = N;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			a[j] = (25ll * g[j - 1] + 26) % mod;
		}
		for (int j = 1; j <= n; ++j) {
			f[j] = f[j - 1] + a[j];
			if (f[j] >= mod) f[j] -= mod;
		}
		for (int j = 1; j <= n; ++j) {
			f[j] += g[j];
			if (f[j] >= mod) f[j] -= mod;
		}
		ans[i] = f[i];
		h = f, f = g, g = h;
	}
	while (T--) {
		scanf("%d", &n);
		printf("%d\n", ans[n]);
	}
	return 0;
}
