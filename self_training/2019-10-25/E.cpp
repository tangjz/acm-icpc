#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e5 + 1;
int tot;
struct Node {
	int fa, lch, rch;
	int key, sz;
	LL val, sum, tag;
} pool[maxn];
inline int randL() {
	return RAND_MAX == 0x7FFF ? rand() << 15 | rand() : rand();
}
inline int newNode(int val) {
	pool[tot].key = randL();
	pool[tot].sz = 1;
	pool[tot].val = pool[tot].sum = val;
	return tot++;
}
inline void upd(int rt) {
	int lch = pool[rt].lch, rch = pool[rt].rch;
	pool[rt].sz = pool[lch].sz + 1 + pool[rch].sz;
	pool[rt].sum = pool[lch].sum + pool[rt].val + pool[rch].sum;
}
inline void push(int rt) {
	LL &adt = pool[rt].tag;
	if(!adt)
		return;
	int lch = pool[rt].lch, rch = pool[rt].rch;
	pool[lch].val += adt;
	pool[lch].tag += adt;
	pool[lch].sum += adt * pool[lch].sz;
	pool[rch].val += adt;
	pool[rch].tag += adt;
	pool[rch].sum += adt * pool[rch].sz;
	adt = 0;
}
inline pair<int, int> split(int rt, int sz) {
	if(!rt)
		return make_pair(0, 0);
	push(rt);
	int lch = pool[rt].lch, rch = pool[rt].rch;
	if(pool[lch].sz + 1 > sz) {
		pool[lch].fa = 0;
		pair<int, int> tr = split(lch, sz);
		pool[rt].lch = lch = tr.second;
		if(lch)
			pool[lch].fa = rt;
		upd(rt);
		return make_pair(tr.first, rt);
	} else {
		pool[rch].fa = 0;
		pair<int, int> tr = split(rch, sz - pool[lch].sz - 1);
		pool[rt].rch = rch = tr.first;
		if(rch)
			pool[rch].fa = rt;
		upd(rt);
		return make_pair(rt, tr.second);
	}
}
inline int merge(int x, int y) {
	if(!x || !y)
		return x | y;
	else if(pool[x].key < pool[y].key) {
		push(x);
		int rch = pool[x].rch;
		pool[rch].fa = 0;
		rch = merge(rch, y);
		pool[x].rch = rch;
		if(rch)
			pool[rch].fa = x;
		upd(x);
		return x;
	} else {
		push(y);
		int lch = pool[y].lch;
		pool[lch].fa = 0;
		lch = merge(x, lch);
		pool[y].lch = lch;
		if(lch)
			pool[lch].fa = y;
		upd(y);
		return y;
	}
}
void insertNode(int &rt, int pos, int val) {
	int lft, rht;
	tie(lft, rht) = split(rt, pos - 1);
	lft = merge(lft, newNode(val));
	rt = merge(lft, rht);
}
void addValue(int &rt, int L, int R, int val) {
	int lft, mid, rht;
	tie(lft, rht) = split(rt, R);
	tie(lft, mid) = split(lft, L - 1);
	pool[mid].val += val;
	pool[mid].tag += val;
	pool[mid].sum += (LL)val * pool[mid].sz;
	lft = merge(lft, mid);
	rt = merge(lft, rht);
}
LL querySum(int &rt, int L, int R) {
	int lft, mid, rht;
	tie(lft, rht) = split(rt, R);
	tie(lft, mid) = split(lft, L - 1);
	LL ret = pool[mid].sum;
	lft = merge(lft, mid);
	rt = merge(lft, rht);
	return ret;
}
int main() {
	int n, rt = 0;
	tot = 1;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		int x;
		scanf("%d", &x);
		insertNode(rt, i, x);
	}
	scanf("%d", &n);
	while(n--) {
		int typ, l, r, v;
		scanf("%d%d", &typ, &l);
		if(typ == 1) {
			insertNode(rt, l, 0);
		} else if(typ == 2) {
			scanf("%d%d", &r, &v);
			addValue(rt, l, r, v);
		} else {
			scanf("%d", &r);
			printf("%lld\n", querySum(rt, l, r));
		}
	}
	return 0;
}