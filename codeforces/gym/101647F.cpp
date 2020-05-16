#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)8e5 + 1;
int tot;
struct Node {
	int lch, rch, key;
	LL x, y, dx, dy;
} pool[maxn];
inline int randL() {
	return RAND_MAX == 0x7FFF ? rand() << 15 | rand() : rand();
}
inline int newNode(LL x, LL y) {
	pool[++tot] = (Node){0, 0, randL(), x, y, 0, 0};
	return tot;
}
inline void addTag(int rt, LL dx, LL dy) {
	if(rt) {
		pool[rt].x += dx;
		pool[rt].dx += dx;
		pool[rt].y += dy;
		pool[rt].dy += dy;
	}
}
inline void pushDown(int rt) {
	if(pool[rt].dx || pool[rt].dy) {
		addTag(pool[rt].lch, pool[rt].dx, pool[rt].dy);
		addTag(pool[rt].rch, pool[rt].dx, pool[rt].dy);
		pool[rt].dx = pool[rt].dy = 0;
	}
}
inline pair<int, int> split(int rt, function<bool(Node const &)> onRight) {
	if(!rt)
		return make_pair(0, 0);
	pushDown(rt);
	if(onRight(pool[rt])) {
		pair<int, int> tp = split(pool[rt].lch, onRight);
		pool[rt].lch = tp.second;
		return make_pair(tp.first, rt);
	} else {
		pair<int, int> tp = split(pool[rt].rch, onRight);
		pool[rt].rch = tp.first;
		return make_pair(rt, tp.second);
	}
}
inline int merge(int x, int y) {
	if(!x || !y)
		return x | y;
	if(pool[x].key < pool[y].key) {
		pushDown(x);
		pool[x].rch = merge(pool[x].rch, y);
		return x;
	} else {
		pushDown(y);
		pool[y].lch = merge(x, pool[y].lch);
		return y;
	}
}
inline int getLeft(int rt) {
	if(!pool[rt].lch)
		return rt;
	pushDown(rt);
	return getLeft(pool[rt].lch);
}
inline int getRight(int rt) {
	if(!pool[rt].rch)
		return rt;
	pushDown(rt);
	return getRight(pool[rt].rch);
}
int n, m, rt;
LL bound;
pair<LL, int> eve[maxn];
int main() {
	scanf("%d%d%lld", &n, &m, &bound);
	for(int i = 0; i < n << 1; ++i) {
		scanf("%lld", &eve[i].first);
		eve[i].second = 1;
	}
	for(int i = n << 1; i < (n + m) << 1; ++i) {
		scanf("%lld", &eve[i].first);
		eve[i].second = 2;
	}
	sort(eve, eve + ((n + m) << 1));
	rt = newNode(0, 0);
	for(int i = 0, msk = 0; i < (n + m) << 1; ) {
		LL cur = eve[i].first;
		for( ; i < (n + m) << 1 && cur == eve[i].first; ++i)
			msk ^= eve[i].second;
		LL len = eve[i].first - cur;
		if(msk == 1) {
			addTag(rt, len, 0);
		} else if(msk == 2) {
			addTag(rt, 0, len);
		} else if(msk == 3) {
			addTag(rt, len, len);
			pair<int, int> tp1 = split(rt, [&bound](Node const &t) {
				return t.x - t.y >= -bound;
			});
			pair<int, int> tp2 = split(tp1.second, [&bound](Node const &t) {
				return t.x - t.y > bound;
			});
			LL xL = -bound, yL = 0; // (-C, 0) - (0, 0)
			LL xR = 0, yR = -bound; // (0, 0) - (0, -C)
			if(tp1.first) {
				int u = getRight(tp1.first); // (x, y) - (x, x + C)
				xL = pool[u].x;
				yL = xL + bound;
			}
			if(tp2.second) {
				int u = getLeft(tp2.second); // (y + C, y) - (x, y)
				yR = pool[u].y;
				xR = yR + bound;
			}
			if(!(xL <= xR && yL <= yR)) {
				int u = getLeft(tp2.first);
				if(!(u && xL <= pool[u].x && yL <= pool[u].y))
					tp2.first = merge(newNode(xL, yL), tp2.first);
			}
			if(!(xR <= xL && yR <= yL) || (xL == xR && yL == yR)) {
				int u = getRight(tp2.first);
				if(!(u && xR <= pool[u].x && yR <= pool[u].y))
					tp2.first = merge(tp2.first, newNode(xR, yR));
			}
			assert(tp2.first != 0);
			addTag(tp2.first, len, len);
			yL = pool[getLeft(tp2.first)].y;
			xR = pool[getRight(tp2.first)].x;
			pair<int, int> tp3 = split(tp1.first, [&yL](Node const &t) {
				return t.y <= yL;
			});
			pair<int, int> tp4 = split(tp2.second, [&xR](Node const &t) {
				return t.x > xR;
			});
			rt = merge(merge(tp3.first, tp2.first), tp4.second);
		}
	}
	printf("%lld\n", pool[getRight(rt)].x);
	return 0;
}
