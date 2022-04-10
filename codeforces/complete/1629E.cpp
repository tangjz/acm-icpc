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

const int maxn = (int)1e3 + 1, maxm = (int)4e6 + 1;
const int maxd = 21, maxc = 26;
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const f64 pi = acos((f64)-1), eps = 1e-12;

inline int sgn(f64 x) {
	return (x > eps) - (x < -eps);
}

void solve() {
	int n;
    static int a[maxn][maxn], b[maxn][maxn];
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            scanf("%d", a[i] + j);
    int ans = 0;
    for(int i = 0; i < n; ++i)
        b[0][i] = 0;
    for(int i = 1; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            b[i][j] = a[i - 1][j];
            if(j > 0)
                b[i][j] ^= b[i - 1][j - 1];
            if(j + 1 < n)
                b[i][j] ^= b[i - 1][j + 1];
            if(i > 1)
                b[i][j] ^= b[i - 2][j];
            ans ^= b[i][j];
        }
    }
    printf("%d\n", ans);
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