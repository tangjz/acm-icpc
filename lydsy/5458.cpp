#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int maxn = 501, mod = 998244353;
int n, m, a[maxn][maxn], b[maxn][maxn << 1 | 1];
inline int mod_sub(int x, int y) {
	return (x -= y) < 0 ? x + mod : x;
}
int mod_inv(int x) {
	return x <= 1 ? x : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			scanf("%d", a[i] + j);
	for(int i = 0; i < n; ++i) {
		b[i][i] = 1;
		for(int j = i - 1; j >= 0; --j) {
			LL tmp = 0;
			for(int k = j + 1; k <= i; ++k) {
				tmp += (LL)a[j][k] * b[k][i];
				if(tmp < 0)
					tmp = (ULL)tmp % mod;
			}
			b[j][i] = (tmp < mod ? tmp : tmp % mod) * mod_inv(mod_sub(a[i][i], a[j][j])) % mod;
		}
		b[i][n + i] = 1;
	}
	for(int i = 0; i < n; ++i) {
		int prd = 1, tmp = a[i][i];
		for(int j = m; j > 0; j >>= 1, tmp = (LL)tmp * tmp % mod)
			(j & 1) && (prd = (LL)prd * tmp % mod);
		for(int j = 0; j <= i; ++j)
			a[j][i] = (LL)b[j][i] * prd % mod;
	}
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < i; ++j) {
			if(!b[j][i])
				continue;
			int prd = mod - b[j][i];
			for(int k = i; k < n + n; ++k)
				b[j][k] = (b[j][k] + (LL)prd * b[i][k]) % mod;
		}
	static LL c[maxn][maxn];
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			c[i][j] = 0;
	for(int i = 0; i < n; ++i)
		for(int j = i; j < n; ++j)
			for(int k = j; k < n; ++k) {
				c[i][k] += (LL)a[i][j] * b[j][n + k];
				if(c[i][k] < 0)
					c[i][k] = (ULL)c[i][k] % mod;
			}
	long long ans1 = 0;
	int ans2 = 0;
	for(int i = 0; i < n; ++i)
		for(int j = i; j < n; ++j) {
			c[i][j] >= mod && (c[i][j] %= mod);
			ans1 += c[i][j];
			ans2 ^= c[i][j];
		}
	printf("%lld %d\n", ans1, ans2);
	return 0;
}
