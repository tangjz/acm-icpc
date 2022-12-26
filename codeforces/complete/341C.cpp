#include <bits/stdc++.h>
using namespace std;

typedef signed i32;
typedef unsigned u32;
typedef long long i64;
typedef unsigned long long u64;
// typedef __int128_t i128;
// typedef __uint128_t u128;
typedef float f32;
typedef double f64;
typedef long double f128;

const int maxn = (int)2e3 + 1, maxm = (int)4e6 + 1;
const int maxd = 21, maxc = 26;
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const f64 pi = acos((f64)-1), eps = 1e-12;

inline int sgn(f64 x) {
	return (x > eps) - (x < -eps);
}

void solve() {
	int n;
	static int f[maxn], bin[maxn][maxn];
	scanf("%d", &n);
	f[0] = 1;
	bin[0][0] = bin[1][0] = bin[1][1] = 1;
	for(int i = 2; i <= n; ++i) {
		f[i] = (i - 1LL) * (f[i - 1] + f[i - 2]) % mod;
		bin[i][0] = bin[i][i] = 1;
		for(int j = 1; j < i; ++j)
			bin[i][j] = (bin[i - 1][j - 1] + bin[i - 1][j]) % mod;
	}
	static int a[maxn];
	static bool vis[maxn] = {};
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		if(a[i] != -1)
			vis[a[i]] = 1;
	}
	int c0 = 0, c2 = 0;
	for(int i = 1; i <= n; ++i) {
		c0 += a[i] == -1 && !vis[i];
		c2 += a[i] != -1 && vis[i];
	}
	int ans = 0, m = (n - c0 - c2) / 2;
	if(!m) {
		ans = f[c0];
	} else {
		for(int i = 0, fct = 1; i <= c0; fct = (i64)fct * (c0 - (i++)) % mod)
			ans = (ans + (i64)fct * bin[i + m - 1][m - 1] % mod * f[c0 - i]) % mod;
		for(int i = 1; i <= m; ++i)
			ans = (i64)ans * i % mod;
	}
	printf("%d\n", ans);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		// printf("%d\n", solve());
		solve();
	}
	return 0;
}
