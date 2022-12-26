#include <bits/stdc++.h>
using namespace std;
const int maxn = 9, maxr = 16, maxc = 10, maxs = 161;
int t, lim, dsu[maxs], idx[maxs], sz[maxn], rep[maxn][maxs], col[maxn][maxs], msk[maxn][maxs], ans[maxn];
char buf[maxr + 1][maxc + 1];
vector<int> e[maxn][maxs];
int dsu_find(int x) {
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
void dsu_merge(int u, int v) {
	u = dsu_find(u);
	v = dsu_find(v);
	if(u == v)
		return;
	if(dsu[u] < dsu[v])
		swap(u, v);
	dsu[v] -= dsu[u] == dsu[v];
	dsu[u] = v;
}
int getGraph(int dep, int sp = -1) {
	if(!dep) {
		int all = maxr * maxc;
		memset(dsu, -1, all * sizeof(int));
		for(int i = 0; i < maxr; ++i)
			for(int j = 0; j < maxc; ++j) {
				int u = j << 4 | i;
				if(i && buf[i - 1][j] == buf[i][j])
					dsu_merge(u, u - 1);
				if(j && buf[i][j - 1] == buf[i][j])
					dsu_merge(u, u - 16);
			}
		sz[dep] = 0;
		for(int i = 0; i < all; ++i)
			if(dsu_find(i) == i) {
				idx[i] = sz[dep]++;
				rep[dep][idx[i]] = i;
				col[dep][idx[i]] = buf[i & 15][i >> 4] - '1';
				msk[dep][idx[i]] = 0;
				vector<int>().swap(e[dep][idx[i]]);
			}
		for(int i = 0; i < all; ++i) {
			int u = idx[dsu_find(i)], x = i & 15, y = i >> 4;
			if(x && buf[x - 1][y] != buf[x][y]) {
				int v = idx[dsu_find(i - 1)];
				msk[dep][u] |= 1 << col[dep][v];
				e[dep][u].push_back(v);
				msk[dep][v] |= 1 << col[dep][u];
				e[dep][v].push_back(u);
			}
			if(y && buf[x][y - 1] != buf[x][y]) {
				int v = idx[dsu_find(i - 16)];
				msk[dep][u] |= 1 << col[dep][v];
				e[dep][u].push_back(v);
				msk[dep][v] |= 1 << col[dep][u];
				e[dep][v].push_back(u);
			}
		}
		return -1;
	}
	memset(dsu, -1, sz[dep - 1] * sizeof(int));
	for(auto it : e[dep - 1][sp])
		if(col[dep - 1][sp] == col[dep - 1][it])
			dsu_merge(sp, it);
	sz[dep] = 0;
	for(int i = 0; i < sz[dep - 1]; ++i)
		if(dsu_find(i) == i) {
			idx[i] = sz[dep]++;
			rep[dep][idx[i]] = rep[dep - 1][i];
			col[dep][idx[i]] = col[dep - 1][i];
			msk[dep][idx[i]] = 0;
			vector<int>().swap(e[dep][idx[i]]);
		}
	for(int i = 0; i < sz[dep - 1]; ++i) {
		int u = idx[dsu_find(i)];
		for(auto it : e[dep - 1][i]) {
			int v = idx[dsu_find(it)];
			if(u == v)
				continue;
			msk[dep][u] |= 1 << col[dep][v];
			e[dep][u].push_back(v);
		}
	}
	for(int i = 0; i < sz[dep]; ++i) {
		sort(e[dep][i].begin(), e[dep][i].end());
		e[dep][i].erase(unique(e[dep][i].begin(), e[dep][i].end()), e[dep][i].end());
	}
	return idx[dsu_find(sp)];
}
bool dfs(int dep, int las = -1) {
	if(dep > lim)
		return 0;
	if(dep == lim || sz[dep] == 1)
		return dep == lim && sz[dep] == 1;
	for(int i = 0; i < sz[dep]; ++i) {
		if(las != -1 && i != las) // Fake!
			continue;
		int ori = col[dep][i];
		for(int j = 0; j < 4; ++j)
			if((msk[dep][i] >> j) & 1) {
				ans[dep] = j << 8 | rep[dep][i];
				col[dep][i] = j;
				int nxt = getGraph(dep + 1, i);
				if(dfs(dep + 1, nxt))
					return 1;
			}
		col[dep][i] = ori;
	}
	return 0;
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d", &lim);
		for(int i = 0; i < maxr; ++i)
			scanf("%s", buf[i]);
		getGraph(0);
		dfs(0);
		printf("Case #%d:\n", Case);
		for(int i = 0; i < lim; ++i)
			printf("%d %d %d\n", (ans[i] >> 8) + 1, (ans[i] & 15) + 1, ((ans[i] >> 4) & 15) + 1);
	}
	return 0;
}
