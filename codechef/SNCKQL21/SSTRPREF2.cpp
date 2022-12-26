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

const int maxn = (int)1e6 + 1, maxm = (int)4e6 + 1;
const int maxd = 21, maxc = 26;
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const f64 pi = acos((f64)-1), eps = 1e-12;

inline int sgn(f64 x) {
	return (x > eps) - (x < -eps);
}

void solve() {
	static char A[maxn], B[maxn], C[maxn];
	scanf("%s%s%s", A, B, C);

	int n = strlen(A), m = strlen(B), q = strlen(C);
	static int f[maxn], g[maxn], h[maxn], *z = f;

	z[0] = n;
	for(int i = 1, L, R = i, x; i < m; ++i) {
		if(i < R && i + z[i - L] < R) {
			z[i] = z[i - L];
			continue;
		}
		for(x = max(i, R); B[x] == B[x - i]; ++x);
		z[i] = x - i;
		if(z[i] > 0) {
			L = i;
			R = x;
		}
	}
	for(int i = 0, L, R = i, x; i < q; ++i) {
		if(i < R && i + z[i - L] < R) {
			h[i] = z[i - L];
			continue;
		}
		for(x = max(i, R); C[x] && C[x] == B[x - i]; ++x);
		h[i] = x - i;
		if(h[i] > 0) {
			L = i;
			R = x;
		}
	}
	h[q] = 0;

	f[0] = f[1] = 0;
	for(int i = 1, j = 0; i < n; ++i) {
		for( ; j && A[i] != A[j]; j = f[j]);
		f[i + 1] = A[i] == A[j] ? (++j) : 0;
	}
	memset(g, -1, (n + 1) * sizeof(int));
	g[0] = max(g[0], h[0]);
	for(int i = 0, j = 0; i < q; ++i) {
		for( ; j && C[i] != A[j]; j = f[j]);
		j += C[i] == A[j];
		g[j] = max(g[j], h[i + 1]);
		j == n && (j = f[j]);
	}

	i64 ans = 0;
	for(int i = n; i >= 0; --i) {
		ans += g[i] + 1;
		g[f[i]] = max(g[f[i]], g[i]);
	}
	printf("%lld\n", ans);
}

int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		// printf("%d\n", solve());
		solve();
	}
	return 0;
}
