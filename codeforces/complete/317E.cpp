#include <bits/stdc++.h>
using namespace std;
const int maxn = 203, maxs = (int)1e6 + 1, maxm = maxn * maxn, DELTA = 101, dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
const char *dir = "LRDU";
int que[maxm], dis[maxm], pre[maxm];
bool ban[maxn][maxn];
void bfs(int rt) {
	memset(dis, -1, sizeof dis);
	dis[rt] = 0;
	que[0] = rt;
	for(int i = 0, tot = 1; i < tot; ++i) {
		int u = que[i], ux = u / maxn, uy = u % maxn;
		for(int d = 0; d < 4; ++d) {
			int vx = ux + dx[d], vy = uy + dy[d];
			if(vx < 0 || vx >= maxn || vy < 0 || vy >= maxn || ban[vx][vy])
				continue;
			int v = vx * maxn + vy;
			if(dis[v] == -1) {
				pre[v] = d;
				dis[v] = dis[u] + 1;
				que[tot++] = v;
			}
		}
	}
}
int sx, sy, tx, ty, n, m, adt[maxm];
char buf[maxs];
inline bool check(int x, int y) {
	return x < 0 || x >= maxn || y < 0 || y >= maxn || !ban[x][y];
}
void append() {
	for(int i = 0; i < m; ++i) {
		if(sx == tx && sy == ty)
			return;
		int d = adt[i];
		if(check(sx + dx[d], sy + dy[d])) {
			sx += dx[d];
			sy += dy[d];
			if(check(tx + dx[d], ty + dy[d])) {
				tx += dx[d];
				ty += dy[d];
			}
			buf[n++] = dir[d];
		}
	}
}
void innerMove(int x, int y) {
	m = 0;
	for(int u = que[0], v = x * maxn + y; u != v; ) {
		int d = pre[v];
		adt[m++] = d;
		v -= dx[d] * maxn + dy[d];
	}
	reverse(adt, adt + m);
	append();
}
int xL, xR, yL, yR;
void outerMove(int sx, int sy, int tx, int ty) {
	m = 0;
	if(tx < xL && sx >= xL) {
		if(yL <= sy && sy <= yR)
			for( ; sy >= yL; --sy)
				adt[m++] = 2;
		for( ; sx >= xL; --sx)
			adt[m++] = 0;
	}
	if(tx > xR && sx <= xR) {
		if(yL <= sy && sy <= yR)
			for( ; sy >= yL; --sy)
				adt[m++] = 2;
		for( ; sx <= xR; ++sx)
			adt[m++] = 1;
	}
	if(ty < yL && sy >= yL) {
		if(xL <= sx && sx <= xR)
			for( ; sx >= xL; --sx)
				adt[m++] = 0;
		for( ; sy >= yL; --sy)
			adt[m++] = 2;
	}
	if(ty > yR && sy <= yR) {
		if(xL <= sx && sx <= xR)
			for( ; sx >= xL; --sx)
				adt[m++] = 0;
		for( ; sy <= yR; ++sy)
			adt[m++] = 3;
	}
	for( ; sx > tx; --sx)
		adt[m++] = 0;
	for( ; sx < tx; ++sx)
		adt[m++] = 1;
	for( ; sy > ty; --sy)
		adt[m++] = 2;
	for( ; sy < ty; ++sy)
		adt[m++] = 3;
	append();
}
int main() {
	scanf("%d%d%d%d%d", &sx, &sy, &tx, &ty, &m);
	if(!m) {
		puts("-1");
		return 0;
	}
	sx += DELTA;
	sy += DELTA;
	tx += DELTA;
	ty += DELTA;
	xL = yL = maxn;
	xR = yR = -1;
	while(m--) {
		int x, y;
		scanf("%d%d", &x, &y);
		ban[x += DELTA][y += DELTA] = 1;
		xL = min(xL, x);
		xR = max(xR, x);
		yL = min(yL, y);
		yR = max(yR, y);
	}
	bfs(sx * maxn + sy);
	if(dis[tx * maxn + ty] == -1) {
		puts("-1");
		return 0;
	}
	if(dis[0] == -1) {
		while(1) {
			innerMove(tx, ty);
			if(sx == tx && sy == ty)
				break;
			bfs(sx * maxn + sy);
		}
	} else {
		innerMove(xL - 1, yL - 1);
		m = 0;
		for(int i = xL - 1; i <= xR + 1; ++i)
			adt[m++] = 0;
		for(int i = yL - 1; i <= yR + 1; ++i)
			adt[m++] = 2;
		append();
		if(xL <= tx && tx <= xR && yL <= ty && ty <= yR) {
			bfs(tx * maxn + ty);
			innerMove(xL - 1, yL - 1);
		}
		if(sx < tx) {
			int y;
			for(y = yL; y <= yR && !ban[xL][y]; ++y);
			outerMove(tx, ty, xL - 1, y);
			outerMove(sx, sy, xL - 1, sy);
		}
		if(sx > tx) {
			int y;
			for(y = yL; y <= yR && !ban[xR][y]; ++y);
			outerMove(tx, ty, xR + 1, y);
			outerMove(sx, sy, xR + 1, sy);
		}
		if(sy < ty) {
			int x;
			for(x = xL; x <= xR && !ban[x][yL]; ++x);
			outerMove(tx, ty, x, yL - 1);
			outerMove(sx, sy, sx, yL - 1);
		}
		if(sy > ty) {
			int x;
			for(x = xL; x <= xR && !ban[x][yR]; ++x);
			outerMove(tx, ty, x, yR + 1);
			outerMove(sx, sy, sx, yR + 1);
		}
	}
	buf[n] = '\0';
	puts(buf);
	return 0;
}