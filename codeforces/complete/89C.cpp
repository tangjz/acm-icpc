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

const int maxn = (int)2e4 + 1, maxm = (int)4e6 + 1;
const int maxd = 21, maxc = 26;
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const f64 pi = acos((f64)-1), eps = 1e-12;

inline int sgn(f64 x) {
	return (x > eps) - (x < -eps);
}

typedef struct {
	int L, R, U, D;
} Node;

void solve() {
	int n, m, q = 0;
	static char buf[maxn];
	static Node info[maxn];
	static pair<int *, int> stk[maxm];
	scanf("%d%d", &n, &m);
	for(int i = 0; i < (n + 2) * (m + 2); ++i)
		info[i] = (Node){i - 1, i + 1, i - (m + 2), i + (m + 2)};
	for(int i = 1, idx = m + 2; i <= n; ++i, idx += m + 2) {
		scanf("%s", buf + idx + 1);
		for(int j = 1; j <= m; ++j) {
			if(buf[idx + j] != '.')
				continue;
			Node &cur = info[idx + j];
			info[cur.L].R = cur.R;
			info[cur.R].L = cur.L;
			info[cur.U].D = cur.D;
			info[cur.D].U = cur.U;
		}
	}
	auto snapshot = [&](int *ptr, int v) {
		stk[q++] = {ptr, *ptr};
		*ptr = v;
	};
	auto rollback = [&]() {
		while(q > 0) {
			--q;
			*stk[q].first = stk[q].second;
		}
	};
	int best = 0, ways = 0;
	for(int x = 1; x <= n; ++x)
		for(int y = 1; y <= m; ++y) {
			int idx = x * (m + 2) + y, i = x, j = y, c = 0;
			if(buf[idx] == '.')
				continue;
			while(i >= 1 && i <= n && j >= 1 && j <= m) {
				++c;
				// printf("#%d: %d %d\n", c, i, j);
				Node &cur = info[idx];
				snapshot(&info[cur.L].R, cur.R);
				snapshot(&info[cur.R].L, cur.L);
				snapshot(&info[cur.U].D, cur.D);
				snapshot(&info[cur.D].U, cur.U);
				switch(buf[idx]) {
					case 'L': {
						idx = info[idx].L;
						break;
					}
					case 'R': {
						idx = info[idx].R;
						break;
					}
					case 'U': {
						idx = info[idx].U;
						break;
					}
					case 'D': {
						idx = info[idx].D;
						break;
					}
				}
				i = idx / (m + 2);
				j = idx % (m + 2);
			}
			if(best < c) {
				best = c;
				ways = 0;
			}
			ways += best == c;
			rollback();
		}
	printf("%d %d\n", best, ways);
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