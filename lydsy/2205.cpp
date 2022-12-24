#include <bits/stdc++.h>
using namespace std;
const int maxe = 4, dx[maxe] = {-1, 0, 1, 0}, dy[maxe] = {0, -1, 0, 1};
const int maxd = 5, maxm = 16, maxv = 34, maxn = maxd * maxd, maxp = maxv >> 1;
int m, p, tot, idx[maxn], dis[maxn], e[maxn][maxe + 1], nxt[maxn][maxn];
char buf[maxd][maxd + 2];
queue<int> Q;
inline int getID(int p0, int p1, int x0, int x1) {
	return (((p0 - 1) * p + (p1 - 1)) * tot + x0) * tot + x1;
}
inline void setID(int val, int &p0, int &p1, int &x0, int &x1) {
	x1 = val % tot;
	val /= tot;
	x0 = val % tot;
	val /= tot;
	p1 = val % p + 1;
	p0 = val / p + 1;
}
inline int getID(int p0, int p1, int p2, int x0, int x1, int x2) {
	return (((((p0 - 1) * (p + 1) + p1) * (p + 1) + p2) * tot + x0) * tot + x1) * tot + x2;
}
inline void setID(int val, int &p0, int &p1, int &p2, int &x0, int &x1, int &x2) {
	x2 = val % tot;
	val /= tot;
	x1 = val % tot;
	val /= tot;
	x0 = val % tot;
	val /= tot;
	p2 = val % (p + 1);
	val /= p + 1;
	p1 = val % (p + 1);
	p0 = val / (p + 1) + 1;
}
int main() {
	const char *pat = "MZz";
	int pos[3] = {-1, -1, -1};
	for(int i = 0; i < maxd; ++i) {
		scanf("%s", buf[i]);
		for(int j = 0; j < maxd; ++j)
			for(int k = 0; k < 3; ++k)
				if(buf[i][j] == pat[k])
					pos[k] = i * maxd + j;
	}
	scanf("%d%d", &m, &p);
	if(p > maxp) {
		puts("LOSE");
		return 0;
	}
	memset(idx, -1, sizeof idx);
	static int ref[maxn];
	memset(ref, -1, sizeof ref);
	ref[0] = pos[0];
	for(idx[pos[0]] = tot++, Q.push(pos[0]); !Q.empty(); Q.pop()) {
		int u = Q.front(), ux = u / maxd, uy = u % maxd;
		for(int i = 0; i < maxe; ++i) {
			int v = u + dx[i] * maxd + dy[i], vx = ux + dx[i], vy = uy + dy[i];
			if(vx < 0 || vx >= maxd || vy < 0 || vy >= maxd || buf[vx][vy] == '1')
				continue;
			if(idx[v] == -1) {
				ref[tot] = v;
				idx[v] = tot++;
				Q.push(v);
			}
			e[idx[u]][++e[idx[u]][0]] = idx[v];
		}
	}
	for(int i = 0; i < 3; ++i)
		pos[i] = idx[pos[i]];
	if(pos[1] == -1 && pos[2] == -1) {
		printf("WIN\n%d\n", p << 1);
		return 0;
	} else if(pos[2] == -1) {
		swap(pos[1], pos[2]);
	}
	for(int i = 0; i < tot; ++i) {
		memset(dis, 0, tot * sizeof(int));
		for(dis[i] = 1, Q.push(i); !Q.empty(); Q.pop()) {
			int u = Q.front();
			for(int j = 1; j <= e[u][0]; ++j) {
				int v = e[u][j];
				if(!dis[v]) {
					dis[v] = dis[u] + 1;
					Q.push(v);
				}
			}
		}
		for(int u = 0; u < tot; ++u) {
			if(dis[u] <= 2) {
				nxt[i][u] = -1;
				continue;
			}
			for(int j = 1; j <= e[u][0]; ++j) {
				int v = e[u][j];
				if(dis[u] == dis[v] + 1) {
					nxt[i][u] = v;
					break;
				}
			}
		}
	}
	map<int, int> dis;
	if(pos[2] == -1) {
		int sta = getID(m, p, pos[0], pos[1]);
		for(dis[sta] = p + 1, Q.push(sta); !Q.empty(); Q.pop()) {
			int u = Q.front(), step = dis[u], p0, p1, x0, x1;
			if(step > maxv)
				continue;
			setID(u, p0, p1, x0, x1);
			for(int i = 0; i <= e[x0][0]; ++i) {
				int y0 = i ? e[x0][i] : x0;
				if(y0 == x1)
					continue;
				int q1 = p1 - !i;
				if(!q1) {
					printf("WIN\n%d\n", step);
					return 0;
				}
				if(step + q1 > maxv)
					continue;
				int q0 = p0 - (nxt[y0][x1] == -1);
				if(!q0)
					continue;
				int y1 = nxt[y0][x1] == -1 ? x1 : nxt[y0][x1];
				int v = getID(q0, q1, y0, y1);
				if(!dis[v]) {
					dis[v] = step + 1;
					Q.push(v);
				}
			}
		}
	} else {
		int sta = getID(m, p, p, pos[0], pos[1], pos[2]);
		for(dis[sta] = 1, Q.push(sta); !Q.empty(); Q.pop()) {
			int u = Q.front(), step = dis[u], p0, p1, p2, x0, x1, x2;
			if(step > maxv)
				continue;
			setID(u, p0, p1, p2, x0, x1, x2);
			for(int i = -1; i <= e[x0][0]; ++i) {
				int y0 = i > 0 ? e[x0][i] : x0;
				if((p1 && y0 == x1) || (p2 && y0 == x2))
					continue;
				int q1 = p1 - (i < 0), q2 = p2 - !i;
				if(q1 < 0 || q2 < 0)
					continue;
				if(!q1 && !q2) {
					printf("WIN\n%d\n", step);
					return 0;
				}
				if(step + q1 + q2 > maxv)
					continue;
				int q0 = p0, y1, y2;
				if(!q1) {
					y1 = y0;
				} else if(nxt[y0][x1] == -1) {
					y1 = x1;
					--q0;
				} else {
					y1 = nxt[y0][x1];
				}
				if(!q2) {
					y2 = y0;
				} else if(nxt[y0][x2] == -1) {
					y2 = x2;
					q0 -= y1 != y2;
				} else {
					y2 = nxt[y0][x2];
				}
				if(q0 <= 0)
					continue;
				if(q1 > q2) {
					swap(q1, q2);
					swap(y1, y2);
				}
				int v = getID(q0, q1, q2, y0, y1, y2);
				if(!dis[v]) {
					dis[v] = step + 1;
					Q.push(v);
				}
			}
		}
	}
	puts("LOSE");
	return 0;
}