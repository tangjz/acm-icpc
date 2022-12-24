#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL;
const int maxn = (int)1e5 + 1, maxm = 33, maxv = (int)1e9;
 
void solve() {
	int n;
	static int a[maxn], p[maxn], s[maxn];
	assert(
		scanf("%d", &n) == 1
		&& 1 <= n && n < maxn
	);
	bool bad = 0;
	int m = 0;
	static int pos[maxm], lim[maxm];
	for(int i = 0, j = n - 1; i < n; ++i) {
		assert(
			scanf("%d", s + i) == 1
			&& 1 <= s[i] && s[i] <= maxv
		);
		if(!i)
			continue;
		int dt = s[i] - s[i - 1] + 1;
		if(dt < 0) {
			bad = 1;
			continue;
		}
		if(!dt) {
			p[i] = j--;
			continue;
		}
		if((2 << m) <= maxv) {
			pos[++m] = i;
			lim[m] = dt;
		} else {
			bad = 1;
		}
	}
	bad |= s[0] < n + m + !!m;
	if(bad) {
		puts("-1");
		return;
	}
	for(int i = m + 1; i <= n; ++i)
		a[i] = 1;
	vector<vector<int> > nxt, cand;
	function<bool(int)> dfs = [&](int dep) -> bool {
		if(!dep) {
			int rem = s[0] - n;
			for(int x: cand[dep])
				rem -= nxt[x][0] - 1;
			if(rem != 0)
				return 0;
			int tot = nxt.size();
			vector<int> sz(tot), pre(tot);
			for(int x = tot - 1; x >= 0; --x) {
				if(nxt[x][1] == -1) {
					sz[x] = 1;
				} else {
					sz[x] = sz[nxt[x][2]] + sz[nxt[x][3]];
				}
			}
			pre[0] = 1;
			for(int x = 0; x < tot; ++x) {
				if(nxt[x][1] == -1) {
					a[pre[x]] = nxt[x][0];
					// printf("assign a[%d]=%d\n", pre[x], nxt[x][0]);
				} else {
					pre[nxt[x][2]] = pre[x];
					pre[nxt[x][3]] = pre[x] + sz[nxt[x][2]];
					p[pos[nxt[x][1]]] = pre[nxt[x][3]] - 1;
					// printf("assign p[%d]=%d\n", pos[nxt[x][1]], pre[nxt[x][3]] - 1);
				}
			}
			return 1;
		}
		for(int x: cand[dep]) {
			if(nxt[x][0] <= lim[dep])
				continue;
			int prd = nxt[x][0], sum = prd - lim[dep] + 1;
			LL delta = (LL)sum * sum - 4LL * prd;
			if(delta < 0)
				continue;
			int rt = sqrtl(delta);
			for( ; (LL)rt * rt <= delta; ++rt);
			for( ; (LL)rt * rt > delta; --rt);
			if((LL)rt * rt != delta || (sum - rt) & 1)
				continue;
			// printf("dep %d: try split %d -> %d %d\n", dep, prd, (sum + rt) / 2, (sum - rt) / 2);
			nxt.push_back({(sum + rt) / 2, -1, -1, -1});
			nxt.push_back({(sum - rt) / 2, -1, -1, -1});
			cand[dep - 1].clear();
			cand[dep - 1].reserve(cand[dep].size() + 1);
			for(int y: cand[dep])
				if(x != y)
					cand[dep - 1].push_back(y);
			nxt[x][1] = dep;
			cand[dep - 1].push_back(nxt[x][2] = nxt.size() - 2);
			cand[dep - 1].push_back(nxt[x][3] = nxt.size() - 1);
			if(dfs(dep - 1))
				return 1;
			nxt[x][1] = nxt[x][2] = nxt[x][3] = -1;
			nxt.pop_back();
			nxt.pop_back();
		}
		return 0;
	};
	nxt.push_back({s[n - 1], -1, -1, -1}); // prd, op idx, cL, cR
	cand.resize(m + 1);
	cand[m] = {0};
	if(!dfs(m)) {
		puts("-1");
		return;
	}
	for(int i = 1; i <= n; ++i)
		printf("%d%c", a[i], " \n"[i == n]);
	for(int i = 1; i < n; ++i)
		printf("%d\n", p[i]);
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