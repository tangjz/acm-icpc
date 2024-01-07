#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, mod = (int)1e9 + 7;
int t, n, m, a[maxn], que[maxn];
vector<int> e[maxn];
bool vis[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		while(m--) {
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		int ans = 0;
		for(int i = 1; i <= n; ++i) {
			if(vis[i])
				continue;
			int tot = 0;
			vis[i] = 1;
			que[tot++] = i;
			int mx = 1;
			for(int j = 0; j < tot; ++j) {
				int u = que[j];
				for( ; mx <= a[u]; mx <<= 1);
				for(int v : e[u])
					if(!vis[v]) {
						vis[v] = 1;
						que[tot++] = v;
					}
			}
			sort(que, que + tot, [&](int const &u, int const &v) {
				return a[u] < a[v];
			});
			for(int j = 1; j < mx; j <<= 1) {
				int cnt = 0, sum = 0;
				for(int k = 0; k < tot; ++k) {
					int u = que[k];
					if(a[u] & j) {
						sum = (sum + (LL)cnt * a[u]) % mod;
						++cnt;
					}
				}
				ans = (ans + (LL)sum * j) % mod;
			}
		}
		printf("%d\n", ans);
		for(int i = 1; i <= n; ++i) {
			vector<int>().swap(e[i]);
			vis[i] = 0;
		}
	}
	return 0;
}
