#include <cmath>
#include <cstdio>
#include <cstring>

typedef long long i64;

constexpr int mod = 1000000007;

int n, m, p;
i64 f[59][209], h[59][209];

int con(int i, int j) {
	if (i <= 0) return 0;
	if (j == 0 && i == 1) return 1;
	if (1 <= j && j < m && i == (int)log10(j) + 1) return 1;
	return 0;
}

int dps(int i, int j) {
	if (i <= 0) return 0;
	i64 &g = f[i][j];
	if (g != -1) return g;
	g = con(i, j);
	g += dps(i - 2, j);
	for (int k = 1; k < i - 1; ++k)
		for (int l = 0; l < m; ++l) {
			g += (i64)dps(k, l) * dps(i - 1 - k - 2, (j - l + m) % m) % mod;
			g += (i64)dps(k, l) * h[i - 1 - k][(j - l + m) % m] % mod;
			g += (i64)dps(k, l) * dps(i - 1 - k - 2, (l - j + m) % m) % mod;
			g += (i64)dps(k, l) * h[i - 1 - k][(l - j + m) % m] % mod;
		}
	return g %= mod;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d%d", &n, &m, &p);
	memset(f, -1, sizeof f);
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < m; ++j)
			h[i][j] = con(i, j);
	printf("%d\n", dps(n, p));
	return 0;
}
