#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)5e3 + 1;
int n, p[5], e[maxn][5], dis[maxn][maxn];
inline bool chk() {
	return p[0] == p[3] || p[1] == p[3] || p[2] == p[3];
}
inline bool upd() {
	printf("%d %d %d\n", p[0], p[1], p[2]);
	fflush(stdout);
	if(chk())
		return 1;
	scanf("%d", p + 3);
	return chk();
}
int main() {
	int m;
	scanf("%d%d", &n, &m);
	while(m--) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u][++e[u][0]] = v;
		e[v][++e[v][0]] = u;
	}
	for(int i = 1; i <= n; ++i) {
		int &deg = e[i][0];
		sort(e[i] + 1, e[i] + deg + 1);
		deg = unique(e[i] + 1, e[i] + deg + 1) - (e[i] + 1);
	}
	for(int i = 1; i <= n; ++i) {
		int *f = dis[i];
		static int que[maxn];
		f[i] = 1;
		que[1] = i;
		for(int j = 1, tot = 1; j <= tot; ++j) {
			int u  = que[j];
			for(int k = 1; k <= e[u][0]; ++k) {
				int v = e[u][k];
				if(!f[v]) {
					f[v] = f[u] + 1;
					que[++tot] = v;
				}
			}
		}
	}
	for(int i = 0; i < 3; ++i)
		p[i] = i + 1;
	if(upd())
		return 0;
	for(int t = 1; t <= n; ++t) {
		int &rt = p[3];
		for(int i = 0; i < 3; ++i)
			if(dis[rt][p[i]] == 2) {
				p[i] = rt;
				upd();
				return 0;
			}
		int low = maxn << 3, q[3];
		for(int i = 1; i <= e[rt][0]; ++i)
			for(int j = 1; j <= e[rt][0]; ++j)
				for(int k = 1; k <= e[rt][0]; ++k) {
					int t[3] = {e[rt][i], e[rt][j], e[rt][k]};
					int tmp = dis[p[0]][t[0]] + dis[p[1]][t[1]] + dis[p[2]][t[2]] + ((i == j) + (j == k) + (i == k)) * maxn;
					if(tmp < low) {
						low = tmp;
						q[0] = t[0];
						q[1] = t[1];
						q[2] = t[2];
					}
				}
		for(int i = 0; i < 3; ++i) {
			int &u = p[i], v = q[i];
			for(int j = 1; j <= e[u][0]; ++j) {
				int w = e[u][j];
				if(dis[v][u] == dis[v][w] + 1) {
					u = w;
					break;
				}
			}
		}
		if(upd())
			return 0;
	}
	return 0;
}
