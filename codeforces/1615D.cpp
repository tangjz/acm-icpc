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

const int maxn = (int)2e6 + 9, maxm = (int)4e6 + 1;
const int maxd = 21, maxc = 26;
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const f64 pi = acos((f64)-1), eps = 1e-12;

inline int sgn(f64 x) {
	return (x > eps) - (x < -eps);
}

typedef struct {
	int u, v, w, c;
} Edge;

void solve() {
	int n, m;
	bool bad = false;
	static int dsu[maxn], dis[maxn];
	static Edge e[maxn];

	scanf("%d%d", &n, &m);
	memset(dsu + 1, -1, n * sizeof(int));
	memset(dis + 1, 0, n * sizeof(int));
	function<int(int)> dsuFind = [&](int x) {
		if(dsu[x] < 0)
			return x;
		int t = dsuFind(dsu[x]);
		dis[x] ^= dis[dsu[x]];
		return dsu[x] = t;
	};
	auto dsuMerge = [&](int u, int v, int w) -> bool {
		int p = dsuFind(u), q = dsuFind(v);
		if(p == q) {
			return (dis[u] ^ dis[v]) == w;
		}
		if(dsu[p] < dsu[q]) {
			swap(p, q);
			swap(u, v);
		}
		dsu[q] -= dsu[p] == dsu[q];
		dsu[p] = q;
		dis[p] = dis[u] ^ dis[v] ^ w;
		assert(dis[p] == 1 || !dis[p]);
		return true;
	};

	for(int i = 1; i < n; ++i) {
		Edge &cur = e[i];
		scanf("%d%d%d", &cur.u, &cur.v, &cur.w);
		if(cur.w == -1)
			continue;
		cur.c = 0;
		for(int tmp = cur.w; tmp > 0; tmp >>= 1)
			if(tmp & 1)
				cur.c = !cur.c;
		if(!bad) {
			bad |= !dsuMerge(cur.u, cur.v, cur.c);
			// if(bad)
			// 	printf("bad: %d %d %d %d\n", cur.u, cur.v, cur.w, cur.c);
		}
	}
	for(int i = 0; i < m; ++i) {
		Edge &cur = e[0];
		scanf("%d%d%d", &cur.u, &cur.v, &cur.c);
		if(!bad) {
			bad |= !dsuMerge(cur.u, cur.v, cur.c);
			// if(bad)
			// 	printf("bad: %d %d -1 %d\n", cur.u, cur.v, cur.c);
		}
	}
	if(bad) {
		puts("NO");
		return;
	}
	puts("YES");
	for(int i = 1; i < n; ++i) {
		Edge &cur = e[i];
		if(cur.w == -1) {
			if(dsuFind(cur.u) == dsuFind(cur.v)) {
				cur.w = dis[cur.u] ^ dis[cur.v];
			} else {
				cur.w = 0;
				dsuMerge(cur.u, cur.v, 0);
			}
		}
		printf("%d %d %d\n", cur.u, cur.v, cur.w);
	}
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