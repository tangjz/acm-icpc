#include <bits/stdc++.h>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef	double DB;
typedef long double LD;

const int mod = (int)1e9 + 7, maxd = 61, maxc = 26;
const int maxn = (int)1e5 + 1, maxm = (int)2e6 + 1;
const DB eps = 1e-9, pi = acos((DB)-1);

inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}

inline void modInc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}

void solve() {
	int n;
	static int w[maxn], deg[maxn], ord[maxn];
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", w + i);
		deg[i] = 0;
		ord[i] = i;
	}
	sort(ord + 1, ord + n + 1, [&](int const &u, int const &v) {
		return w[u] < w[v];
	});
	for(int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		++deg[u];
		++deg[v];
	}
	static LL ans[maxn];
	ans[n - 1] = 0;
	for(int i = 1; i <= n; ++i)
		ans[n - 1] += (LL)deg[i] * w[i];
	for(int i = 1, j = n - 1; i <= n; ++i) {
		int u = ord[i];
		for(int k = 1; k < deg[u]; ++k, --j)
			ans[j - 1] = ans[j] - w[u];
	}
	for(int i = 1; i < n; ++i)
		printf("%lld%c", ans[i], " \n"[i == n - 1]);
}

int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}
