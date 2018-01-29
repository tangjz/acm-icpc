#include <bits/stdc++.h>
typedef long long LL;
const int maxn = 705, maxd = 10, mod = (int)1e9 + 7;
int len, c[maxn][maxn], pw[maxd + 1][maxn], f[maxd + 1][maxn], g[maxd + 1][maxn], rem, cnt[maxd + 1];
char buf[maxn];
int main() {
	scanf("%s", buf);
	len = strlen(buf);
	c[0][0] = 1;
	for(int i = 0; i <= maxd; ++i)
		pw[i][0] = 1;
	for(int i = 1; i <= len; ++i) {
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j)
			(c[i][j] = c[i - 1][j - 1] + c[i - 1][j]) >= mod && (c[i][j] -= mod);
		for(int j = 0; j <= maxd; ++j)
			pw[j][i] = (LL)pw[j][i - 1] * j % mod;
	}
	rem = len;
	for(int i = 0; i < len; ++i) {
		for(int j = 0; '0' + j < buf[i]; ++j) {
			--rem;
			for(int k = j; k < maxd; ++k)
				++cnt[k];
			for(int i = 0; i < maxd; ++i) {
				for(int j = 0; j <= rem; ++j)
					g[i][j] = (LL)c[rem][j] * pw[i + 1][j] % mod * pw[maxd - i - 1][rem - j] % mod;
				for(int j = rem - 1; j >= 0; --j)
					(g[i][j] += g[i][j + 1]) >= mod && (g[i][j] -= mod);
			}
			for(int i = 1; i <= len; ++i)
				for(int j = 0; j < maxd; ++j) {
					int ways = i - cnt[j] <= rem ? g[j][std::max(i - cnt[j], 0)] : 0;
					(f[j][i] += ways) >= mod && (f[j][i] -= mod);
				}
			++rem;
			for(int k = j; k < maxd; ++k)
				--cnt[k];
		}
		--rem;
		for(int k = buf[i] - '0'; k < maxd; ++k)
			++cnt[k];
	}
	int ans = 0;
	std::sort(buf, buf + len);
	for(int i = 0; i < len; ++i)
		ans = (10LL * ans + buf[i] - '0') % mod;
	for(int i = 1; i < maxd; ++i)
		for(int j = 1; j <= len; ++j)
			ans = (ans + (LL)(f[i][j] - f[i - 1][j]) * i * pw[maxd][len - j]) % mod;
	ans < 0 && (ans += mod);
	printf("%d\n", ans);
	return 0;
}
