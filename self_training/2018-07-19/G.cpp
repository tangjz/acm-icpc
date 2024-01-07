#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 51, maxd = 12, maxs = 1 << 12 | 1, mod = (int)1e9 + 7;
int n, m, q, inv[maxn];
vector<int> e[maxn];
struct Info {
	int val, ways;
	void upd(Info const &t) {
		val > t.val && (val = t.val, ways = 0);
		val == t.val && (ways += t.ways) >= mod && (ways -= mod);
	}
	Info merge(Info const &t) const {
		int fir = val + t.val;
		if(fir >= n)
			return (Info){n, 0};
		int sec = (LL)ways * t.ways % mod;
		return (Info){fir, sec};
	}
} f[maxs][maxn], g[maxs][maxn];
int tot, vis[maxn], dis[maxn], ord[maxn];
vector<int> adt[maxn];
int main() {
	inv[1] = 1;
	for(int i = 2; i < maxn; ++i)
		inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
	while(scanf("%d%d%d", &n, &q, &m) == 3) {
		for(int i = 0; i < n; ++i)
			vector<int>().swap(e[i]);
		while(q--) {
			int u, v;
			scanf("%d%d", &u, &v);
			--u;
			--v;
			e[u].push_back(v);
			e[v].push_back(u);
		}
		for(int i = 0; i < 1 << m; ++i)
			for(int j = 0; j < n; ++j)
				f[i][j] = g[i][j] = (Info){n, 0};
		for(int i = 0; i < n; ++i) {
			int cur = i < m ? 1 << i : 0;
			f[cur][i] = g[cur][i] = (Info){0, 1};
		}
		memset(vis, -1, n * sizeof(int));
		for(int msk = 0; msk < 1 << m; ++msk) {
			for(int i = 0; i < n; ++i) {
				int cur = i < m ? 1 << i : 0;
				if(cur && !(msk & cur))
					continue;
				int rem = msk ^ cur, lbt = rem & -rem;
				if(rem)
					for(int msk2 = (rem - 1) & rem; msk2; msk2 = (msk2 - 1) & rem)
						if(msk2 & lbt) {
							int u = msk2 | cur, v = (rem ^ msk2) | cur;
							g[msk][i].upd(f[u][i].merge(g[v][i]));
						}
				if(g[msk][i].val < n)
					adt[g[msk][i].val].push_back(i);
			}
			tot = 0;
			for(int i = 0, j = 0; i < n; ++i) {
				for(auto u : adt[i]) {
					if(vis[u] != msk) {
						vis[u] = msk;
						dis[u] = n;
					}
					if(dis[u] > i) {
						dis[u] = i;
						ord[tot++] = u;
					}
				}
				vector<int>().swap(adt[i]);
				for( ; j < tot; ++j) {
					int u = ord[j];
					if(dis[u] > i)
						break;
					for(auto v : e[u]) {
						int cur = v < m ? 1 << v : 0;
						if(cur && !(msk & cur))
							continue;
						if(vis[v] != msk) {
							vis[v] = msk;
							dis[v] = n;
						}
						if(dis[v] > dis[u] + 1) {
							dis[v] = dis[u] + 1;
							ord[tot++] = v;
						}
					}
				}
			}
			for(int i = 0; i < tot; ++i) {
				int u = ord[i];
				for(auto v : e[u]) {
					int msk2 = msk | (v < m ? 1 << v : 0);
					Info tmp = g[msk][u];
					++tmp.val;
					f[msk2][v].upd(tmp);
					g[msk2][v].upd(tmp);
				}
			}
		}
		Info ans = (Info){n, 0};
		for(int i = 0; i < n; ++i)
			ans.upd(g[(1 << m) - 1][i]);
		if(ans.val < n) {
			ans.ways = (LL)ans.ways * inv[ans.val + 1] % mod;
			printf("%d\n", ans.ways);
		} else {
			puts("0");
		}
	}
	return 0;
}
