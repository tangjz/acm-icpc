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
const int mod = 998244353, maxd = 10, maxc = 26;
const int maxn = (int)2e3 + 1, maxm = (int)2e6 + 1;

void dfs(int u, int sz[maxn], vector<int> e[maxn << 1 | 1], int dp[maxn << 1 | 1][maxn]) {
	int cnt = 0;
	dp[u][0] = 0;
	for(int v : e[u]) {
		dfs(v, sz, e, dp);
		int nxt = cnt + sz[v];
		if(!cnt) {
			memcpy(dp[u], dp[v], (nxt + 1) * sizeof(int));
		} else {
			static int tmp[maxn];
			memset(tmp, 0, (nxt + 1) * sizeof(int));
			for(int i = 0; i <= cnt; ++i) if(dp[u][i])
				for(int j = 0; j <= sz[v]; ++j) if(dp[v][j])
					tmp[i + j] = (tmp[i + j] + (LL)dp[u][i] * dp[v][j]) % mod;
			memcpy(dp[u], tmp, (nxt + 1) * sizeof(int));
		}
		cnt = nxt;
	}
	(dp[u][1] += 1) >= mod && (dp[u][1] -= mod);
	// printf("dp %d:", u+1);
	// for(int i = 0; i <= sz[u]; ++i)
	// 	printf(" %d", dp[u][i]);
	// printf("\n");
}

void solve() {
	int n, m = 0;
	static int dis[maxn][maxn];
	static pair<int, pair<int, int> > seq[maxm];
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j) {
			scanf("%d", dis[i] + j);
			if(i < j)
				seq[m++] = make_pair(dis[i][j], make_pair(i, j));
		}
	sort(seq, seq + m);

	int tot = n;
	static int dsu[maxn], cntE[maxn], rep[maxn << 1 | 1], sz[maxn << 1 | 1];
	static vector<int> e[maxn << 1 | 1];
	for(int i = 0; i < tot; ++i) {
		dsu[i] = -1;
		cntE[i] = 0;
		rep[i] = i;
		sz[i] = 1;
	}
	function<int(int)> dsu_find = [&](int x) -> int {
		return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
	};
	auto dsu_merge = [&](int u, int v) -> void {
		u = dsu_find(u);
		v = dsu_find(v);
		if(u == v) {
			++cntE[u];
			return;
		}
		if(dsu[u] < dsu[v])
			swap(u, v);
		dsu[v] += dsu[u];
		dsu[u] = v;
		cntE[v] += cntE[u] + 1;
	};
	for(int i = 0; i < m; ++i) {
		int u, v;
		tie(u, v) = seq[i].second;
		dsu_merge(u, v);
		int x = dsu_find(u), cntV = -dsu[x];
		if(cntE[x] != cntV * (cntV - 1) / 2)
			continue;
		// O(n) times
		unordered_set<int> ids;
		sz[tot] = 0;
		for(int j = 0; j < n; ++j)
			if(dsu_find(j) == x) {
				ids.insert(rep[j]);
				rep[j] = tot;
				++sz[tot];
			}
		// printf("%d (%d):", tot+1, sz[tot]);
		for(int x : ids) {
			// printf(" %d (%d)", x+1, sz[x]);
			e[tot].push_back(x);
		}
		// puts("");
		++tot;
	}
	static int dp[maxn << 1 | 1][maxn];
	dfs(tot - 1, sz, e, dp);
	for(int i = 1; i <= n; ++i)
		printf("%d%c", dp[tot - 1][i], " \n"[i == n]);
	for(int i = 0; i < tot; ++i)
		vector<int>().swap(e[i]);
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