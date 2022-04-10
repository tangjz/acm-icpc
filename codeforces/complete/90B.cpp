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

const int maxn = (int)1e2 + 1, maxm = (int)1e4 + 1;
const int maxd = 21, maxc = 26;
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const f64 pi = acos((f64)-1), eps = 1e-12;

inline int sgn(f64 x) {
	return (x > eps) - (x < -eps);
}

void solve() {
    int n, m;
    static int row[maxc + 1][maxn], col[maxc + 1][maxn];
    static char buf[maxm];
    scanf("%d%d", &n, &m);
    for(int i = 0; i < maxc; ++i) {
        memset(row[i], 0, n * sizeof(int));
        memset(col[i], 0, m * sizeof(int));
    }
    for(int i = 0, idx = 0; i < n; ++i) {
        scanf("%s", buf + idx);
        for(int j = 0; j < m; ++j, ++idx) {
            int o = buf[idx] - 'a';
            ++row[o][i];
            ++col[o][j];
        }
    }
    int sz = 0;
    for(int i = 0, idx = 0; i < n; ++i)
        for(int j = 0; j < m; ++j, ++idx) {
            int o = buf[idx] - 'a';
            if(row[o][i] == 1 && col[o][j] == 1)
                buf[sz++] = buf[idx];
        }
    buf[sz] = '\0';
    puts(buf);
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