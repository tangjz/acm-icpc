#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxd = 17, seed = 29;
int tot, rt, pw[maxn];
struct Node {
	int lch, rch, key, sz, val, sum;
} pool[maxn];
inline int randL() {
	return RAND_MAX == 0x7FFF ? rand() << 15 | rand() : rand();
}
inline int newNode(int val) {
	pool[++tot].key = randL();
	pool[tot].sz = 1;
	pool[tot].val = pool[tot].sum = val;
	return tot;
}
inline void upd(int rt) {
	int lch = pool[rt].lch, rch = pool[rt].rch;
	pool[rt].sz = pool[lch].sz + 1 + pool[rch].sz;
	pool[rt].sum = (pool[lch].sum * pw[1] + pool[rt].val) * pw[pool[rch].sz] + pool[rch].sum;
}
inline pair<int, int> split(int rt, int sz) {
	if(!rt)
		return make_pair(0, 0);
	int lch = pool[rt].lch, rch = pool[rt].rch;
	if(pool[lch].sz + 1 > sz) {
		pair<int, int> tr = split(lch, sz);
		pool[rt].lch = lch = tr.second;
		upd(rt);
		return make_pair(tr.first, rt);
	} else {
		pair<int, int> tr = split(rch, sz - pool[lch].sz - 1);
		pool[rt].rch = rch = tr.first;
		upd(rt);
		return make_pair(rt, tr.second);
	}
}
inline int merge(int x, int y) {
	if(!x || !y)
		return x | y;
	else if(pool[x].key < pool[y].key) {
		pool[x].rch = merge(pool[x].rch, y);
		upd(x);
		return x;
	} else {
		pool[y].lch = merge(x, pool[y].lch);
		upd(y);
		return y;
	}
}
inline int getVal(int sta, int len) {
	pair<int, int> tr = split(rt, sta);
	pair<int, int> tr2 = split(tr.second, len);
	int ret = pool[tr2.first].sum;
	tr.second = merge(tr2.first, tr2.second);
	rt = merge(tr.first, tr.second);
	return ret;
}
int main() {
	int q, x, y;
	static char buf[maxn];
	pw[0] = 1;
	for(int i = 1; i < maxn; ++i)
		pw[i] = pw[i - 1] * seed;
	scanf("%s", buf);
	for(int i = 0; buf[i]; ++i)
		rt = merge(rt, newNode(buf[i] - 'a' + 1));
	scanf("%d", &q);
	while(q--) {
		scanf("%s%d", buf, &x);
		if(buf[0] == 'Q') {
			scanf("%d", &y);
			if(x > y)
				swap(x, y);
			int ans = 0;
			for(int i = maxd - 1; i >= 0; --i)
				if(1 << i <= tot - y + 1 && getVal(x - 1, 1 << i) == getVal(y - 1, 1 << i)) {
					ans += 1 << i;
					x += 1 << i;
					y += 1 << i;
				}
			printf("%d\n", ans);
		} else {
			scanf("%s", buf + 2);
			y = buf[2] - 'a' + 1;
			pair<int, int> tr = split(rt, x);
			if(buf[0] == 'R') {
				pair<int, int> tr2 = split(tr.first, x - 1);
				pool[tr2.second].val = pool[tr2.second].sum = y;
				tr.first = merge(tr2.first, tr2.second);
			} else {
				tr.second = merge(newNode(y), tr.second);
			}
			rt = merge(tr.first, tr.second);
		}
	}
	return 0;
}
