#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 51, mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
int n, mx, dt, e[maxn][maxn];
char buf[maxn];
bool vis[maxn << 1 | 1];
inline void upd_min(int &x, int y) {
	x > y && (x = y);
}
inline void upd_add(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
pair<int, int> dfs(int u, int k, int b) {
	pair<int, int> ret = make_pair(INF, INF), tmp;
	if(k > 0) {
		vis[u] = 1;
		upd_min(ret.first, b);
		for(int v = 0; v < n; ++v)
			if(e[u][v] != -1 && !vis[n + v]) {
				tmp = dfs(v, -k, e[u][v] - dt - b);
				upd_min(ret.first, tmp.first);
				upd_min(ret.second, tmp.second);
			}
	} else {
		vis[n + u] = 1;
		upd_min(ret.second, b);
		for(int v = 0; v < n; ++v)
			if(e[v][u] != -1 && !vis[v]) {
				tmp = dfs(v, -k, e[v][u] - dt - b);
				upd_min(ret.first, tmp.first);
				upd_min(ret.second, tmp.second);
			}
	}
	return ret;
}
int main() {
	n = 1;
	mx = 9;
	memset(e, -1, sizeof e);
	for(int i = 0; i < n; ++i) {
		scanf("%s", buf);
		n = strlen(buf);
		for(int j = 0; j < n; ++j)
			if(buf[j] == '-') {
				e[i][j] = -1;
			} else {
				e[i][j] = buf[j] - '0';
				mx = min(mx, e[i][j]);
			}
	}
	int ans = 0;
	for(dt = 0; dt <= mx; ++dt) {
		memset(vis, 0, sizeof vis);
		int f[2][4] = {}, cur = 0, pre = 1;
		f[cur][0] = 1;
		for(int i = 0; i < n; ++i) {
			if(vis[i])
				continue;
			pair<int, int> res = dfs(i, 1, 0);
			swap(cur, pre);
			memset(f[cur], 0, sizeof f[0]);
			for(int j = -res.first; j <= res.second; ++j) {
				int msk = (j == -res.first) << 1 | (j == res.second);
				for(int k = 0; k < 4; ++k)
					upd_add(f[cur][msk | k], f[pre][k]);
			}
		}
		upd_add(ans, f[cur][3]);
	}
	printf("%d\n", ans);
	return 0;
}
