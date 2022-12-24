#include <bits/stdc++.h>
using namespace std;
const int maxn = 17, maxd = 1 << 16 | 1;
int n, m, trans[maxn][maxd], pre[maxd], dis[maxd], que[maxd];
char buf[maxd];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			scanf("%d", trans[j] + (1 << i));
	for(int i = 0; i < m; ++i)
		for(int j = 1; j < 1 << n; ++j) {
			int k = j & -j;
			trans[i][j] = k < j ? trans[i][k] | trans[i][j ^ k] : 1 << trans[i][j];
		}
	memset(dis, -1, sizeof dis);
	que[0] = (1 << n) - 1;
	dis[que[0]] = 0;
	for(int i = 0, tot = 1; i < tot; ++i) {
		int u = que[i];
		for(int j = 0; j < m; ++j) {
			int v = trans[j][u];
			if(dis[v] == -1) {
				pre[v] = u;
				dis[v] = dis[u] + 1;
				que[tot++] = v;
			}
		}
	}
	if(dis[1] == -1) {
		puts("impossible");
	} else {
		for(int u, v = 1; v != que[0]; v = u) {
			u = pre[v];
			for(int i = 0; i < m; ++i)
				if(trans[i][u] == v) {
					buf[dis[u]] = i < 10 ? '0' + i : 'a' + i - 10;
					break;
				}
		}
		puts(buf);
	}
	return 0;
}
