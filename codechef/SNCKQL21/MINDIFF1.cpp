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

bool check(vector<vector<int> > &edges, int lim, vector<int> &ord) {
	int n = edges.size(), m = 0;
	vector<int> deg(n);
	vector<bool> inQue(n);
	for(int i = 0; i < n; ++i) {
		deg[i] = edges[i].size();
		if(deg[i] <= lim) {
			ord[m++] = i;
			inQue[i] = 1;
		}
	}
	for(int i = 0; i < m; ++i) {
		int u = ord[i];
		for(int v: edges[u]) {
			if(inQue[v])
				continue;
			--deg[v];
			if(deg[v] <= lim) {
				ord[m++] = v;
				inQue[v] = 1;
			}
		}
	}
	return m == n;
}

void solve() {
	int n, m;
	scanf("%d%d", &n, &m);
	vector<vector<int> > edges(n);
	for(int i = 0; i < m; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		--u;
		--v;
		edges[u].push_back(v);
		edges[v].push_back(u);
	}
	int L = 0, R = n - 1;
	vector<int> ord(n);
	while(L < R) {
		int M = (L + R) >> 1;
		if(check(edges, M, ord)) {
			R = M;
		} else {
			L = M + 1;
		}
	}
	check(edges, L, ord);
	printf("%d\n", L);
	vector<int> res(n);
	for(int i = 0; i < n; ++i)
		res[ord[i]] = n - i;
	auto it = res.begin();
	for(int i = 0; i < n; ++i) {
		printf("%d%c", *(it++), " \n"[i == n - 1]);
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
