#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e5 + 1, mod = (int)1e9 + 7;
int n, m, a[maxn];
struct Segment {
	LL cnt;
	int sum;
} seg[maxn << 1 | 1];
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
inline void seg_merge(Segment &rt, Segment &lch, Segment &rch) {
	rt.cnt = lch.cnt + rch.cnt;
	(rt.sum = lch.sum + rch.sum) >= mod && (rt.sum -= mod);
}
void seg_build(int L, int R) {
	int rt = seg_idx(L, R);
	if(L == R) {
		int v;
		scanf("%d", &v);
		seg[rt] = (Segment){(LL)v, (int)((LL)a[L] * v % mod)};
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	seg_build(L, M);
	seg_build(M + 1, R);
	seg_merge(seg[rt], seg[lch], seg[rch]);
}
void seg_upd(int L, int R, int x, int v) {
	int rt = seg_idx(L, R);
	if(L == R) {
		seg[rt] = (Segment){(LL)v, (int)((LL)a[L] * v % mod)};
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(x <= M)
		seg_upd(L, M, x, v);
	else
		seg_upd(M + 1, R, x, v);
	seg_merge(seg[rt], seg[lch], seg[rch]);
}
Segment seg_que(int L, int R, int x) {
	if(R <= x)
		return seg[seg_idx(L, R)];
	int M = (L + R) >> 1;
	if(x <= M)
		return seg_que(L, M, x);
	Segment ret = seg_que(M + 1, R, x);
	seg_merge(ret, seg[seg_idx(L, M)], ret);
	return ret;
}
int seg_find(int L, int R, LL v) {
	while(L < R) {
		int M = (L + R) >> 1;
		if(seg[seg_idx(L, M)].cnt >= v) {
			R = M;
		} else {
			v -= seg[seg_idx(L, M)].cnt;
			L = M + 1;
		}
	}
	return L;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		a[i] -= i;
	}
	seg_build(1, n);
	while(m--) {
		int x, y;
		scanf("%d%d", &x, &y);
		if(x < 0) {
			seg_upd(1, n, -x, y);
		} else {
			Segment lft = x > 1 ? seg_que(1, n, x - 1) : (Segment){0LL, 0};
			Segment rht = seg_que(1, n, y);
			int M = seg_find(1, n, (lft.cnt + rht.cnt + 1) >> 1);
			Segment mid = seg_que(1, n, M);
			int res = ((mid.cnt - lft.cnt) % mod * a[M] - (LL)(mid.sum - lft.sum)
				+ (LL)(rht.sum - mid.sum) - (rht.cnt - mid.cnt) % mod * a[M]) % mod;
			printf("%d\n", res < 0 ? res + mod : res);
		}
	}
	return 0;
}
