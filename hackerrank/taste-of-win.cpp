#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e7 + 1, mod = (int)1e9 + 7;
int n, m, pw, ways, f[maxn];
int main() {
	scanf("%d%d", &n, &m);
	++pw;
	for(int i = 0; i < m; ++i)
		(pw <<= 1) >= mod && (pw -= mod);
	f[0] = ways = 1;
	for(int i = 1; i <= n; ++i) {
		f[i] = (ways - f[i - 1] - (i - 1LL) * (pw - i + 1) % mod * f[i - 2]) % mod;
		ways = (LL)ways * (pw - i) % mod;
	}
	f[n] < 0 && (f[n] += mod);
	(ways -= f[n]) < 0 && (ways += mod);
	printf("%d\n", ways);
	return 0;
}
