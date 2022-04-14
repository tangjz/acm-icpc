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
    scanf("%d", &n);
    vector<vector<int> > pos(n + 1);
    for(int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        pos[x].push_back(i);
    }
    vector<int> ans;
    for(int i = 1; i <= n; ) {
        int v = 0, j = i;
        for( ; ; ++v) {
            auto it = lower_bound(pos[v].begin(), pos[v].end(), i);
            if(it == pos[v].end())
                break;
            j = max(j, *it + 1);
        }
        if(j == i)
            j = i + 1;
        i = j;
        ans.push_back(v);
    }
    int m = ans.size();
    printf("%d\n", m);
    for(int i = 0; i < m; ++i)
        printf("%d%c", ans[i], " \n"[i == m - 1]);
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