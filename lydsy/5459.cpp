#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxp = 51, maxm = (int)1e3 + 3, mod = 998244353;
int n, p, m, cnt[maxp], inv[maxm], ways[maxm], bin[maxm], f[2][maxp][maxm], cur, pre = 1;
int main() {
	inv[1] = 1;
	for(int i = 2; i < maxm; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	scanf("%d%d%d", &n, &p, &m);
	{ // get cnt[0: p)
		static int pos[maxp] = {};
		for(int i = 1, v = 1 % p; i <= n; ++i, v = 10 * v % p) {
			if(pos[v]) {
				for(int j = 0, k = i, len = i - pos[v]; j < len && k <= n; ++j, ++k, v = 10 * v % p)
					cnt[v] += (n - k) / len + 1;
				break;
			}
			pos[v] = i;
			++cnt[v];
		}
	}
	f[cur][0][0] = 1;
	for(int i = 0; i < p; ++i) {
		if(!cnt[i])
			continue;
		for(int j = 0, coeff = 1; j <= m; ++j) {
			ways[j] = coeff;
			coeff = (LL)coeff * (j + cnt[i]) % mod * inv[j + 1] % mod;
		}
		for(int j = 0, k = 0, coeff = 1; j <= cnt[i] && k <= m; ++j, k += 10) {
			bin[j] = j & 1 ? mod - coeff : coeff;
			coeff = (LL)coeff * (cnt[i] - j) % mod * inv[j + 1] % mod;
		}
		for(int j = m; j >= 0; --j)
			for(int k = j - 10, x = 1; x <= cnt[i] && k >= 0; k -= 10, ++x)
				ways[j] = (ways[j] + (LL)bin[x] * ways[k]) % mod;
		swap(cur, pre);
		for(int j = 0; j < p; ++j)
			memset(f[cur][j], 0, (m + 1) * sizeof(int));
		for(int x = 0; x < p; ++x)
			for(int j = 0; j <= m; ++j) {
				if(!f[pre][x][j])
					continue;
				for(int k = j, y = x; k <= m; ++k, (y += i) >= p && (y -= p))
					f[cur][y][k] = (f[cur][y][k] + (LL)f[pre][x][j] * ways[k - j]) % mod;
			}
	}
	for(int i = 0, ans = 0; i <= m; ++i) {
		(ans += f[cur][0][i]) >= mod && (ans -= mod);
		printf("%d%c", ans, " \n"[i == m]);
	}
	return 0;
}
