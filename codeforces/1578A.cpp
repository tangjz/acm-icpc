#include <bits/stdc++.h>
using namespace std;
 
const int maxc = 7, maxd = 51;
const int maxn = 2501, maxs = 6.25e6 + 1, INF = 0x3f3f3f3f;
 
char mat[maxd][maxd], ans[maxn][maxn];
int r, c, n, m, tot, seq[maxn], sta[maxn];
int sz[maxn], rem[maxn][maxn];
pair<int, int> pos[maxn][maxc], que[maxs];
pair<int, char> op[maxn][maxn];
 
int main() {
	scanf("%d%d", &r, &c);
	int rc = r * c;
	for(int i = 0; i < r; ++i)
		scanf("%s", mat[i]);
	for(int i = 0; i < r; ++i)
		for(int j = 0; j < c; ++j) {
			if(mat[i][j] < 'a' || mat[i][j] > 'z')
				continue;
			char ch = mat[i][j];
			int &cnt = sz[n] = 0, *cRem = rem[n];
			pair<int, int> *cPos = pos[n];
			mat[i][j] = '.';
			cPos[cnt++] = {i, j};
			for(int o = 0; o < cnt; ++o) {
				int ux, uy;
				tie(ux, uy) = cPos[o];
				for(int dx = -1; dx <= 1; ++dx)
					for(int dy = -1; dy <= 1; ++dy) {
						if(!dx == !dy)
							continue;
						int vx = ux + dx, vy = uy + dy;
						if(vx < 0 || vx >= r || vy < 0 || vy >= c || mat[vx][vy] != ch)
							continue;
						mat[vx][vy] = '.';
						cPos[cnt++] = {vx, vy};
					}
			}
			memset(cRem, 0x3f, rc * sizeof(int));
			for(int u = 0, ux = 0; ux < r; ++ux)
				for(int uy = 0; uy < c; ++uy, ++u) {
					cRem[u] = 0;
					for(int o = 0; o < cnt; ++o) {
						int vx = ux - cPos[0].first + cPos[o].first;
						int vy = uy - cPos[0].second + cPos[o].second;
						if(vx < 0 || vx >= r || vy < 0 || vy >= c) {
							cRem[u] = INF;
							break;
						}
						cRem[u] += mat[vx][vy] != '.';
					}
				}
			ch = ch - 'a' + 'A';
			for(int o = 0; o < cnt; ++o) {
				int ux, uy;
				tie(ux, uy) = cPos[o];
				mat[ux][uy] = ch;
			}
			int s = i * c + j;
			op[n][s] = {-1, 'S'};
			que[tot++] = {n, s};
			sta[n++] = -1;
		}
	for(int i = 0; i < tot; ++i) {
		int id, u;
		tie(id, u) = que[i];
		if(sta[id] != -1)
			continue;
		pair<int, char> *cOp = op[id];
		int ux = u / c, uy = u % c;
		if(!ux) {
			sta[id] = uy;
			char *cAns = ans[id];
			for(int v = u; v != -1; v = cOp[v].first)
				*(cAns++) = cOp[v].second;
			*cAns = '\0';
			seq[m++] = id;
 
			pair<int, int> *cPos = pos[id];
			for(int jd = 0; jd < n; ++jd) {
				if(sta[jd] != -1)
					continue;
				int *nRem = rem[jd];
				pair<int, int> *nPos = pos[jd];
				pair<int, char> *nOp = op[jd];
				for(int j = 0; j < sz[id]; ++j)
					for(int k = 0; k < sz[jd]; ++k) {
						int vx = cPos[j].first - nPos[k].first + nPos[0].first;
						int vy = cPos[j].second - nPos[k].second + nPos[0].second;
						if(vx < 0 || vx >= r || vy < 0 || vy >= c)
							continue;
						int v = vx * c + vy;
						if((--nRem[v]) > 0)
							continue;
						bool stp = 0;
						for(int dx = 0; !stp && dx <= 1; ++dx)
							for(int dy = -1; !stp && dy <= 1; ++dy) {
								if(!dx == !dy)
									continue;
								int u = v + dx * c + dy, ux = vx + dx, uy = vy + dy;
								if(ux < 0 || ux >= r || uy < 0 || uy >= c || !nOp[u].second)
									continue;
								nOp[v] = {u, dx > 0 ? 'D' : (dy > 0 ? 'R' : 'L')};
								que[tot++] = {jd, v};
								stp = 1;
							}
					}
			}
			continue;
		}
		int *cRem = rem[id];
		for(int dx = -1; dx <= 0; ++dx)
			for(int dy = -1; dy <= 1; ++dy) {
				if(!dx == !dy)
					continue;
				int v = u + dx * c + dy, vx = ux + dx, vy = uy + dy;
				if(vx < 0 || vx >= r || vy < 0 || vy >= c || cRem[v] || cOp[v].second)
					continue;
				cOp[v] = {u, dx < 0 ? 'D' : (dy < 0 ? 'R' : 'L')};
				que[tot++] = {id, v};
			}
	}
	if(m < n) {
		puts("-1");
	} else {
		printf("%d\n", n);
		for(int i = n - 1; i >= 0; --i) {
			int u = seq[i];
			printf("%d %s\n", sta[u] + 1, ans[u]);
		}
	}
	return 0;
}