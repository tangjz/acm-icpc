#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL;
const int maxn = (int)2e5 + 1, maxv = (int)1e9;
const char *pat = "RPS";
 
int ptot;
struct Node {
	int cL, cR, key, cnt;
	int val, vL, vR;
} pool[maxn];
inline int randL() {
	return RAND_MAX == 0x7FFF ? rand() << 15 | rand() : rand();
}
inline int newNode(int val) {
	pool[ptot] = (Node){
		0, 0, randL(), 1,
		val, val, val,
	};
	return ptot++;
}
inline void upd(int rt) {
	int lch = pool[rt].cL, rch = pool[rt].cR;
	pool[rt].cnt = pool[lch].cnt + 1 + pool[rch].cnt;
	pool[rt].vL = pool[lch].cnt ? pool[lch].vL : pool[rt].val;
	pool[rt].vR = pool[rch].cnt ? pool[rch].vR : pool[rt].val;
}
inline pair<int, int> split(int rt, int sz) {
	if(!rt)
		return make_pair(0, 0);
	int lch = pool[rt].cL, rch = pool[rt].cR;
	if(pool[lch].cnt + 1 > sz) {
		pair<int, int> tr = split(lch, sz);
		pool[rt].cL = tr.second;
		upd(rt);
		return make_pair(tr.first, rt);
	}
	pair<int, int> tr = split(rch, sz - pool[lch].cnt - 1);
	pool[rt].cR = tr.first;
	upd(rt);
	return make_pair(rt, tr.second);
}
inline int merge(int x, int y) {
	if(!x || !y)
		return x | y;
	if(x == y) {
		puts("error");
	}
	if(pool[x].key < pool[y].key) {
		pool[x].cR = merge(pool[x].cR, y);
		upd(x);
		return x;
	}
	pool[y].cL = merge(x, pool[y].cL);
	upd(y);
	return y;
}
void dfs(int rt) {
	if(!rt)
		return;
	dfs(pool[rt].cL);
	putchar(pat[pool[rt].val]);
	dfs(pool[rt].cR);
}
inline void print(int rt, int sta) {
	printf("[%d, %d]: ", sta, sta + pool[rt].cnt - 1);
	dfs(rt);
	puts("");
}
 
void solve() {
	int n, m;
	static char buf[maxn];
	assert(
		scanf("%d%d%s", &n, &m, buf) == 3
		&& 1 <= n && n < maxn
		&& 1 <= m && m < maxn
		&& strlen(buf) == n
	);
	static int rt[maxn];
	set<int> segL;
	ptot = 1;
	for(int i = 1, las = -1; i <= n; ++i) {
		int o = -1;
		for(int j = 0; j < 3; ++j)
			if(buf[i - 1] == pat[j]) {
				o = j;
				break;
			}
		assert(o != -1);
		rt[i] = newNode(o);
		if(las != -1 && pool[rt[las]].vR != (o + 1) % 3) {
			rt[las] = merge(rt[las], rt[i]);
		} else {
			segL.insert(i);
			las = i;
		}
		// printf("update ");
		// print(rt[las], las);
	}
	while(m--) {
		int typ, u, v;
		assert(
			scanf("%d", &typ) == 1
			&& 1 <= typ && typ <= 2
		);
		if(typ == 2) {
			assert(
				scanf("%d", &u) == 1
				&& 1 <= u && u <= n
			);
			int pL = *(--segL.upper_bound(u)), ofs = u - pL;
			pair<int, int> tr = split(rt[pL], ofs);
			printf("%c\n", pat[pool[tr.second].vL]);
			rt[pL] = merge(tr.first, tr.second);
			continue;
		}
		assert(
			scanf("%d%d", &u, &v) == 2
			&& 1 <= u && u <= v && v <= n
		);
		int pL = *(--segL.upper_bound(u)), pR = pL + pool[rt[pL]].cnt; // [pL, pR)
		int ofs = u - pL;
		// printf("fetch ");
		// print(rt[pL], pL);
		pair<int, int> tr = split(rt[pL], ofs);
		// shift
		if(v < pR) {
			int ofs2 = v - u + 1;
			pair<int, int> tr2 = split(tr.second, ofs2);
			int vL = pool[tr2.first].vL, vR = pool[tr2.first].vR;
			pair<int, int> tr3 = split(tr2.first, 1);
			pool[tr3.first].val = vR;
			upd(tr3.first);
			tr2.first = merge(tr3.second, tr3.first);
			tr.second = merge(tr2.first, tr2.second);
			rt[pL] = merge(tr.first, tr.second);
			// printf("update ");
			// print(rt[pL], pL);
		} else {
			int vL = pool[tr.second].vL, vR = pool[tr.second].vR;
			pair<int, int> tr2 = split(tr.second, 1);
			pool[tr2.first].val = vR;
			upd(tr2.first);
			tr.second = merge(tr2.second, tr2.first);
			if(pool[tr.first].cnt && pool[tr.first].vR == (pool[tr.second].vL + 1) % 3) {
				// printf("split [%d, %d) [%d, %d)\n", pL, pL + pool[tr.first].cnt, pL + pool[tr.first].cnt, pR);
				// printf("update ");
				rt[pL] = tr.first;
				// print(rt[pL], pL);
				pL += pool[tr.first].cnt;
				rt[pL] = tr.second;
				segL.insert(pL);
			} else {
				rt[pL] = merge(tr.first, tr.second);
			}
		}
		// printf("update ");
		// print(rt[pL], pL);
		for(int qR; pR <= v; pR = qR) { // [pL, pR) [pR, qR)
			qR = pR + pool[rt[pR]].cnt;
			// printf("fetch ");
			// print(rt[pR], pR);
			int cur = pool[rt[pL]].vR, pre = (cur + 2) % 3, nxt = (cur + 1) % 3;
			pair<int, int> tr = v < qR ? split(rt[pR], v - pR + 1) : make_pair(rt[pR], 0);
			pair<int, int> tr2 = {0, tr.first};
			// ->
			while(pool[tr2.second].cnt && pool[tr2.second].vL == pre) {
				pair<int, int> tr3 = split(tr2.second, 1);
				pool[tr3.first].val = cur;
				upd(tr3.first);
				tr2 = {merge(tr2.first, tr3.first), tr3.second};
			}
			if(pool[tr2.first].cnt) {
				segL.erase(pR);
				rt[pL] = merge(rt[pL], tr2.first);
				pR = pL + pool[rt[pL]].cnt;
				if(pR == qR) {
					// printf("update ");
					// print(rt[pL], pL);
					continue;
				}
				tr.first = tr2.second;
				segL.insert(pR);
			}
			// <-
			if(pool[tr.first].cnt && pool[tr.first].vL == nxt) {
				tr2 = split(rt[pL], pool[rt[pL]].cnt - 1);
				pool[tr2.second].val = nxt;
				upd(tr2.second);
				// printf("modify %d: %c\n", pR - 1, pat[nxt]);
				if(pool[tr2.first].cnt && pool[tr2.first].vR == (pool[tr2.second].vL + 1) % 3) {
					// printf("split [%d, %d) [%d, %d)\n", pL, pL + pool[tr2.first].cnt, pL + pool[tr2.first].cnt, pR);
					// printf("update ");
					rt[pL] = tr2.first;
					// print(rt[pL], pL);
					pL += pool[rt[pL]].cnt;
					rt[pL] = tr2.second;
					segL.insert(pL);
				} else {
					rt[pL] = merge(tr2.first, tr2.second);
				}
			}
			// shift
			if(pool[tr.first].cnt) {
				int vL = pool[tr.first].vL, vR = pool[tr.first].vR;
				pair<int, int> tr2 = split(tr.first, 1);
				pool[tr2.first].val = vR;
				upd(tr2.first);
				tr.first = merge(tr2.second, tr2.first);
			}
			rt[pR] = merge(tr.first, tr.second);
			if(pool[rt[pL]].vR == (pool[rt[pR]].vL + 1) % 3) {
				// printf("update ");
				// print(rt[pL], pL);
				pL = pR;
				continue;
			}
			rt[pL] = merge(rt[pL], rt[pR]);
			segL.erase(pR);
			// printf("update ");
			// print(rt[pL], pL);
		}
		// check if split u with (u-1)
		pL = *(--segL.upper_bound(u));
		if(pL == u)
			continue;
		pR = pL + pool[rt[pL]].cnt;
		ofs = u - pL;
		tr = split(rt[pL], ofs);
		if(pool[tr.first].vR == (pool[tr.second].vL + 1) % 3) {
			// printf("split [%d, %d) [%d, %d)\n", pL, u, u, pR);
			rt[pL] = tr.first;
			rt[u] = tr.second;
			segL.insert(u);
		} else {
			rt[pL] = merge(tr.first, tr.second);
		}
	}
}
 
int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}