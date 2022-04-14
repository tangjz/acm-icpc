#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cctype>
#include <cstdio>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <functional>
#include <unordered_set>
#include <unordered_map>
using namespace std;

typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef	double DB;
typedef long double LD;

const int mod = (int)1e9 + 7, maxd = 10, maxc = 26;
const int maxn = (int)2e5 + 1, maxm = (int)2e6 + 1;
const DB eps = 1e-9, pi = acos((DB)-1);

inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}

void solve() {
	int n, m;
	static int w[maxn], dsu[maxn];
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n + m; ++i) {
		scanf("%d", w + i);
		dsu[i] = -1;
	}
	LL ans = 0;
	vector<pair<int, pair<int, int> > > edges;
	for(int i = 1; i <= n; ++i) {
		int sz, j, cost;
		scanf("%d", &sz);
		while(sz--) {
			scanf("%d", &j);
			j += n;
			edges.push_back(make_pair(cost = w[i] + w[j], make_pair(i, j)));
			ans += cost;
		}
	}
	sort(edges.begin(), edges.end());
	reverse(edges.begin(), edges.end());
	function<int(int)> dsu_find = [&](int x) -> int {
		return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
	};
	auto dsu_merge = [&](int u, int v) -> bool {
		u = dsu_find(u);
		v = dsu_find(v);
		if(u == v)
			return 0;
		if(dsu[u] < dsu[v])
			swap(u, v);
		dsu[v] -= dsu[u] == dsu[v];
		dsu[u] = v;
		return 1;
	};
	for(auto &it : edges) {
		int u, v;
		tie(u, v) = it.second;
		if(dsu_merge(u, v))
			ans -= it.first;
	}
	printf("%lld\n", ans);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}