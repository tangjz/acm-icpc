#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, mod = (int)1e9 + 7;
int t, n, m, a[maxn], b[maxn], c[maxn], f[maxn], que[maxn];
vector<int> e[maxn];
bool can[maxn];
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) {
			scanf("%d%d", a + i, b + i);
			e[a[i]].push_back(i);
			e[b[i]].push_back(i);
		}
		m = 0;
		memset(can + 1, 0, n * sizeof(bool));
		que[m++] = 1;
		can[1] = 1;
		for(int i = 0; i < m; ++i) {
			int u = que[i];
			for(int v : e[u])
				if(!can[v]) {
					can[v] = 1;
					que[m++] = v;
				}
		}
		m = 0;
		for(int i = 1; i <= n; ++i) {
			scanf("%d", c + i);
			if(c[i])
				que[m++] = i;
		}
		can[1] = 0;
		

		m = min(n + 1, 1000);
		memset(f[cur] + 1, 0, n * sizeof(int));
		f[cur][1] = 1;
		for(int i = 1; i <= m; ++i) {
			swap(cur, pre);
			for(int j = 1; j <= n; ++j)
				if(vis[a[j]] || vis[b[j]])
					(f[cur][j] = f[pre][a[j]] + f[pre][b[j]]) >= mod && (f[cur][j] -= mod);
				else
					f[cur][j] = f[pre][j];
		}
		bool chk = 1;
		for(int i = 1; i <= n; ++i) {
			chk &= !c[i] || f[cur][i] == f[pre][i];
			vector<int>().swap(e[i]);
		}
		if(!chk) {
			printf("Case #%d: UNBOUNDED\n", Case);
		} else {
			int sum = 0;
			for(int i = 1; i <= n; ++i)
				sum = (sum + (LL)f[cur][i] * c[i]) % mod;
			printf("Case #%d: %d\n", Case, sum);
		}
	}
	return 0;
}
