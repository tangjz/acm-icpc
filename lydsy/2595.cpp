#include <bits/stdc++.h>
using namespace std;
const int maxn = 13, maxp = 101, maxs = 1 << 10 | 1, INF = 0x3f3f3f3f;
const int maxd = 4, dx[maxd] = {-1, 1, 0, 0}, dy[maxd] = {0, 0, -1, 1};
int n, m, tot, ctr, x[maxp], y[maxp], pos[maxn][maxn], s[maxp], w[maxp], f[maxs][maxp], g[maxs][maxp];
std::priority_queue<std::pair<int, int> > Q;
bool vis[maxp], used[maxp];
void dfs(int msk, int u) {
	used[u] = 1;
	if(g[msk][u] == -1)
		return;
	int v = g[msk][u] >> ctr, msk2 = g[msk][u] & ((1 << ctr) - 1);
	if(u == v) {
		dfs(msk2 | s[v], v);
		dfs((msk ^ msk2) | s[v], v);
	} else {
		dfs(msk2, v);
	}
}
int main() {
	scanf("%d%d", &n, &m);
	memset(f, 0x3f, sizeof f);
	memset(g, -1, sizeof g);
	memset(pos, -1, sizeof pos);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) {
			scanf("%d", w + tot);
			if(!w[tot]) {
				s[tot] = 1 << (ctr++);
				f[s[tot]][tot] = 0;
			}
			x[tot] = i;
			y[tot] = j;
			pos[i][j] = tot++;
		}
	for(int msk = 0; msk < 1 << ctr; ++msk) {
		int *dis = f[msk], *pre = g[msk];
		for(int i = 0; i < tot; ++i) {
			if(s[i] && !(msk & s[i]))
				continue;
			for(int msk2 = msk; msk2; msk2 = (msk2 - 1) & msk) {
				int tmp = f[msk2 | s[i]][i] + f[(msk ^ msk2) | s[i]][i] - w[i];
				if(tmp < dis[i]) {
					dis[i] = tmp;
					pre[i] = i << ctr | msk2;
				}
			}
			if(dis[i] < INF)
				Q.push(make_pair(-dis[i], i));
		}
		memset(vis, 0, sizeof vis);
		while(!Q.empty()) {
			int u = Q.top().second;
			Q.pop();
			if(vis[u])
				continue;
			vis[u] = 1;
			int ux = x[u], uy = y[u];
			for(int o = 0; o < maxd; ++o) {
				int vx = ux + dx[o], vy = uy + dy[o], v = pos[vx][vy];
				if(v == -1)
					continue;
				int msk2 = msk | s[v], tmp = dis[u] + w[v];
				if(tmp < f[msk2][v]) {
					f[msk2][v] = tmp;
					g[msk2][v] = u << ctr | msk;
					if(msk == msk2)
						Q.push(make_pair(-dis[v], v));
				}
			}
		}
	}
	for(int i = 0; i < tot; ++i)
		if(s[i]) {
			printf("%d\n", f[(1 << ctr) - 1][i]);
			dfs((1 << ctr) - 1, i);
			for(int j = 1; j <= n; ++j) {
				for(int k = 1; k <= m; ++k) {
					int u = pos[j][k];
					putchar(s[u] ? 'x' : (used[u] ? 'o' : '_'));
				}
				putchar('\n');
			}
			break;
		}
	return 0;
}
