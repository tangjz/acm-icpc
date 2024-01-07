#include <cstdio>
const int maxn = 200001, maxs = 8000001;
int n, m, rt[maxn], tot, pL[maxs], pR[maxs], dsu[maxs];
void build(int &rt, int L, int R) {
	rt = tot++;
	if(L == R) {
		dsu[rt] = -1;
		return;
	}
	int M = (L + R) >> 1;
	build(pL[rt], L, M);
	build(pR[rt], M + 1, R);
}
void update(int &rt, int L, int R, int x, int v) {
	pL[tot] = pL[rt];
	pR[tot] = pR[rt];
	rt = tot++;
	if(L == R) {
		dsu[rt] = v;
		return;
	}
	int M = (L + R) >> 1;
	if(x <= M)
		update(pL[rt], L, M, x, v);
	else
		update(pR[rt], M + 1, R, x, v);
}
int query(int rt, int L, int R, int x) {
	while(L < R) {
		int M = (L + R) >> 1;
		if(x <= M) {
			R = M;
			rt = pL[rt];
		} else {
			L = M + 1;
			rt = pR[rt];
		}
	}
	return dsu[rt];
}
int dsu_find(int &rt, int x, int &dep) {
	int info = query(rt, 1, n, x);
	if(info < 0) {
		dep = info;
		return x;
	}
	info = dsu_find(rt, info, dep);
	update(rt, 1, n, x, info);
	return info;
}
int main() {
	scanf("%d%d", &n, &m);
	build(rt[0], 1, n);
	for(int i = 1; i <= m; ++i) {
		int typ, x, y;
		static int lastans = 0;
		scanf("%d", &typ);
		if(typ == 2) {
			scanf("%d", &x);
			x ^= lastans;
		} else {
			scanf("%d%d", &x, &y);
			x ^= lastans;
			y ^= lastans;
		}
		rt[i] = rt[i - 1];
		if(typ == 1) {
			int dx, dy;
			x = dsu_find(rt[i], x, dx);
			y = dsu_find(rt[i], y, dy);
			if(x == y)
				continue;
			if(dx < dy) {
				update(rt[i], 1, n, y, x);
			} else if(dx > dy) {
				update(rt[i], 1, n, x, y);
			} else {
				update(rt[i], 1, n, x, --dx);
				update(rt[i], 1, n, y, x);
			}
		} else if(typ == 2) {
			rt[i] = rt[x];
		} else {
			int tp;
			x = dsu_find(rt[i], x, tp);
			y = dsu_find(rt[i], y, tp);
			puts((lastans = x == y) ? "1" : "0");
		}
	}
	return 0;
}