#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e5 + 1;

int n, a[maxn], m, b[maxn], q;
pair<int, int> eve[maxn];

struct Node {
	int cnt, sum, tag;
	void apply(int val) {
		tag = val;
		sum = cnt * val;
	}
} seg[maxn << 1 | 1];

inline int segIdx(int L, int R) {
	return (L + R) | (L < R);
}

inline void segUp(int rt, int lch, int rch) {
	seg[rt].sum = seg[lch].sum + seg[rch].sum;
}

inline void segDown(int rt, int lch, int rch) {
	if(seg[rt].tag == -1)
		return;
	seg[lch].apply(seg[rt].tag);
	seg[rch].apply(seg[rt].tag);
	seg[rt].tag = -1;
}

int segInit(int L, int R) {
	int rt = segIdx(L, R);
	seg[rt] = (Node){R - L + 1, 0, -1};
	if(L == R) {
		seg[rt].sum += b[L];
	} else {
		int M = (L + R) >> 1;
		segUp(rt, segInit(L, M), segInit(M + 1, R));
	}
	return rt;
}

void segUpd(int L, int R, int l, int r, int v) {
	int rt = segIdx(L, R);
	if(l <= L && R <= r) {
		seg[rt].apply(v);
		return;
	}
	int M = (L + R) >> 1, lch = segIdx(L, M), rch = segIdx(M + 1, R);
	segDown(rt, lch, rch);
	if(l <= M)
		segUpd(L, M, l, r, v);
	if(r > M)
		segUpd(M + 1, R, l, r, v);
	segUp(rt, lch, rch);
}

int segQue(int L, int R, int l, int r) {
	int rt = segIdx(L, R);
	if(l <= L && R <= r)
		return seg[rt].sum;
	int M = (L + R) >> 1, lch = segIdx(L, M), rch = segIdx(M + 1, R), ret = 0;
	segDown(rt, lch, rch);
	if(l <= M)
		ret += segQue(L, M, l, r);
	if(r > M)
		ret += segQue(M + 1, R, l, r);
	// segUp(rt, lch, rch);
	return ret;
}

int main() {
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = 1; i <= q; ++i)
		scanf("%d%d", &eve[i].first, &eve[i].second);
	int L = 1, R = n, mid = (n + 1) >> 1;
	while(L < R) {
		m = (L + R) >> 1;
		for(int i = 1; i <= n; ++i)
			b[i] = a[i] > m;
		segInit(1, n);
		for(int i = 1; i <= q; ++i) {
			int u = eve[i].first, v = eve[i].second;
			bool rev = 0;
			if(u > v) {
				swap(u, v);
				rev = 1;
			}
			int cnt = segQue(1, n, u, v), len = v - u + 1;
			if(rev) {
				if(cnt < len)
					segUpd(1, n, u + cnt, v, 0);
				if(cnt)
					segUpd(1, n, u, u + cnt - 1, 1);
			} else {
				if(cnt < len)
					segUpd(1, n, u, v - cnt, 0);
				if(cnt)
					segUpd(1, n, v - cnt + 1, v, 1);
			}
		}
		if(segQue(1, n, mid, mid)) {
			L = m + 1;
		} else {
			R = m;
		}
	}
	printf("%d\n", L);
	return 0;
}