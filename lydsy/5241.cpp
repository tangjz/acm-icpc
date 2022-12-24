#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 251;
int t, n, m, x[maxn], inv[maxn], phi[maxn], f[maxn], g[maxn], a[maxn], b[maxn];
int main() {
	scanf("%d%d", &t, &m);
	for(int i = 0; i < t; ++i) {
		scanf("%d", x + i);
		n = std::max(n, x[i]);
	}
	for(int i = 1; i <= n; ++i) {
		inv[i] = i > 1 ? m - (int)(m / i * (LL)inv[m % i] % m) : 1;
		phi[i] += i;
		for(int j = i + i; j <= n; j += i)
			phi[j] -= phi[i];
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j < i; ++j) {
			g[i] = (g[i] + (LL)a[j] * g[i - j]) % m;
			b[i] = (b[i] + (LL)b[j] * g[i - j]) % m;
		}
		g[i] = i > 1 ? (LL)g[i] * inv[i - 1] % m : 1;
		b[i] = (b[i] + (LL)i * g[i]) % m;
		for(int j = 1, k = i; k <= n; ++j, k += i) {
			f[k] = (f[k] + (LL)b[i] * phi[j]) % m;
			(a[k] += f[i]) >= m && (a[k] -= m);
		}
		f[i] = (LL)f[i] * inv[i] % m;
	}
	for(int i = 0; i < t; ++i)
		printf("%d\n", f[x[i]]);
	return 0;
}