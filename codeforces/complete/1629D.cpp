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
	int n;
    static int st = 0, tim2[maxc + 1][maxc + 1] = {}, tim3[maxc + 1][maxc + 1][maxc + 1] = {};
    ++st;
    bool ans = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        static char buf[4];
        scanf("%s", buf);
        if(ans)
            continue;
        int len = strlen(buf);
        if(buf[0] == buf[len - 1]) {
            ans = 1;
            continue;
        }
        if(len == 2) {
            int u = buf[0] - 'a', v = buf[1] - 'a';
            if(tim2[v][u] == st) {
                ans = 1;
                continue;
            }
            for(int w = 0; w < maxc; ++w)
                if(tim3[v][u][w] == st) {
                    ans = 1;
                    break;
                }
            tim2[u][v] = st;
        } else { // len == 3
            int u = buf[0] - 'a', v = buf[1] - 'a', w = buf[2] - 'a';
            if(tim2[w][v] == st || tim3[w][v][u] == st) {
                ans = 1;
            }
            tim3[u][v][w] = st;
        }
    }
    puts(ans ? "YES" : "NO");
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