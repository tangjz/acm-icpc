#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e5 + 1;
const LL INF = ~0ULL >> 1;
int t, n, m, sta[3], dis[3][maxn];
vector<int> e[maxn];
LL p[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i < 3; ++i)
			scanf("%d", sta + i);
		for(int i = 1; i <= m; ++i)
			scanf("%lld", p + i);
		sort(p + 1, p + m + 1);
		for(int i = 0; i < m; ++i) {
			p[i + 1] += p[i];
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		for(int i = 0; i < 3; ++i) {
			int *f = dis[i];
			static int que[maxn];
			memset(f + 1, -1, n * sizeof(int));
			f[sta[i]] = 0;
			que[0] = sta[i];
			for(int j = 0, tot = 1; j < tot; ++j) {
				int u = que[j];
				for(int &v : e[u])
					if(f[v] == -1) {
						f[v] = f[u] + 1;
						que[tot++] = v;
					}
			}
		}
		LL ans = INF;
		for(int i = 1; i <= n; ++i) {
			int com = dis[1][i], all = com + dis[0][i] + dis[2][i];
			LL tmp = ans;
			if(all <= m)
				ans = min(ans, p[com] + p[all]);
		}
		printf("%lld\n", ans);
		for(int i = 1; i <= n; ++i)
			vector<int>().swap(e[i]);
	}
	return 0;
}