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

const int maxn = (int)2e5 + 9, maxm = (int)4e6 + 1;
const int maxd = 21, maxc = 26;
const int mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const f64 pi = acos((f64)-1), eps = 1e-12;

inline int sgn(f64 x) {
	return (x > eps) - (x < -eps);
}

int n, dep[maxn], f[maxn], up[maxn];
vector<int> e[maxn], leaves;

void dfs(int u, int p) {
	bool isLeaf = true;
	f[u] = up[u] = u;
	for(int v: e[u]) {
		if(v == p)
			continue;
		isLeaf = false;
		dep[v] = dep[u] + 1;
		dfs(v, u);
		if(dep[f[u]] < dep[f[v]]) {
			f[u] = f[v];
		}
	}
	up[f[u]] = u;
	if(isLeaf)
		leaves.push_back(u);
}

void solve() {
	int m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dep[1] = 0;
	dfs(1, -1);
	sort(leaves.begin(), leaves.end(), [&](int const &u, int const &v) {
		int lft = dep[u] - dep[up[u]];
		int rht = dep[v] - dep[up[v]];
		return lft > rht;
	});
	int rem = n;
	i64 ans = LLONG_MIN;
	for(int i = 0; i < m; ++i) {
		if(i < (int)leaves.size()) {
			int u = leaves[i];
			rem -= dep[u] - dep[up[u]] + 1;
		}
		int r = i + 1, b = min(rem, n >> 1), w = n - r - b;
		ans = max(ans, (i64)w * (r - b));
	}
	printf("%lld\n", ans);
	vector<int>().swap(leaves);
	for(int i = 1; i <= n; ++i)
		vector<int>().swap(e[i]);
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