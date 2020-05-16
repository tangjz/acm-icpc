#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e3 + 1, maxl = maxn * 20 + 1;
const LL INF = (LL)1e18 + 1;
int main() {
	int n, s;
	scanf("%d%d", &n, &s);
	
	int mx = 0;
	static int c[maxn];
	for(int i = 0; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		for( ; mx < u; c[++mx] = -1);
		c[u] = max(c[u], v);
	}
	mx = min(mx, s);
	
	int mod = 0;
	for(int i = 1; i <= mx; ++i)
		if(c[i] != -1 && (!mod || (LL)c[mod] * i < (LL)c[i] * mod))
			mod = i;
 
	int bound = (mod - 1) * mx;
	if(s < bound + mod) {
		int tot = 0;
		static int pos[maxl];
		static LL dp[maxl];
		for(int L = s, R = s; L <= R; ) {
			for(int i = R; i >= L; --i)
				pos[tot++] = i;
			R = min((R + mx) >> 1, L - 1);
			L = max((L - mx + 1) >> 1, 0);
		}
		reverse(pos, pos + tot);
		for(int i = 0; i <= mx; ++i)
			assert(pos[i] == i);
		memset(dp, 0, tot * sizeof(LL));
		for(int i = 1; i <= mx; ++i)
			if(c[i] != -1)
				for(int j = i; j <= mx; ++j)
					dp[j] = max(dp[j], dp[j - i] + c[i]);
		for(int i = mx + 1, pL = 0, pR = 0; i < tot; ++i) {
			int u = pos[i];
			for(int L = max((u - mx + 1) >> 1, 0); pos[pL] < L; ++pL);
			for(int R = min((u + mx) >> 1, u - 1); pos[pR] < R; ++pR);
			for(int j = pL, k = pR; j <= k; ++j) {
				for( ; j <= k && pos[j] + pos[k] > u; --k);
				if(j <= k) {
					assert(pos[j] + pos[k] == u);
					dp[i] = max(dp[i], dp[j] + dp[k]);
				}
			}
		}
		printf("%lld\n", dp[tot - 1]);
		return 0;
	}
 
	static LL rep[maxn];
	rep[0] = 0;
	for(int i = 1; i < mod; ++i)
		rep[i] = -INF;
 
	for(int i = 1; i <= mx; ++i) {
		if(c[i] == -1 || i == mod)
			continue;
		static bool vis[maxn];
		memset(vis, 0, mod * sizeof(bool));
		for(int j = 0; j < mod; ++j) {
			if(vis[j])
				continue;
			int tot = 0, upp = 0;
			static int que[maxn];
			for(int k = j; !vis[k]; k = (k + i) % mod) {
				que[tot++] = k;
				vis[k] = 1;
				if(rep[que[upp]] < rep[k])
					upp = tot - 1;
			}
			auto next_pos = [&](int pos) {
				return pos + 1 < tot ? pos + 1 : 0;
			};
			if(rep[que[upp]] != -INF)
				for(int k = 0, u = upp, v = next_pos(u); k < tot + tot; ++k, u = v, v = next_pos(u))
					rep[que[v]] = max(rep[que[v]], rep[que[u]] + c[i] - (que[u] + i - que[v]) / mod * (LL)c[mod]);
		}
	}
 
	LL ans = 0;
	for(int i = 0; i < mod; ++i)
		ans = max(ans, rep[i] + (s - i) / mod * (LL)c[mod]);
	printf("%lld\n", ans);
	return 0;
}