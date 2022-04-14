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

const int maxn = (int)2e3 + 1, maxm = (int)4e3 + 1;
const int maxd = 21, maxc = 26;
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const f64 pi = acos((f64)-1), eps = 1e-12;

inline int sgn(f64 x) {
	return (x > eps) - (x < -eps);
}

typedef struct {
	int cnt, sum;
} Info;

inline void append(Info &dst, Info const &src, int w) {
	dst.cnt = (dst.cnt + src.cnt) % mod;
	dst.sum = (dst.sum + src.sum + (i64)src.cnt * w) % mod;
}

void solve() {
	int n;
	static char s[maxn], t[maxn];
	scanf("%d%s%s", &n, s, t);
	static int cur = 0, pre = 1;
	static Info dp[2][maxm];
	dp[cur][n + 0] = (Info){1, 0};
	for(int i = 0; i < n; ++i) {
		swap(cur, pre);
		memset(dp[cur] + n - (i + 1), 0, ((i + 1) << 1 | 1) * sizeof(Info));
		int xL, xR, yL, yR;
		if(s[i] == '?') {
			xL = 0;
			xR = 1;
		} else {
			xL = xR = (s[i] - '0') ^ (i & 1);
		}
		if(t[i] == '?') {
			yL = 0;
			yR = 1;
		} else {
			yL = yR = (t[i] - '0') ^ (i & 1);
		}
		for(int j = -i; j <= i; ++j) {
			for(int x = xL; x <= xR; ++x)
				for(int y = yL; y <= yR; ++y) {
					int jj = j + x - y;
					append(dp[cur][n + jj], dp[pre][n + j], abs(jj));
				}
		}
	}
	printf("%d\n", dp[cur][n + 0].sum);
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