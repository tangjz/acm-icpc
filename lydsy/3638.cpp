#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, maxk = 21, maxd = 17 << 1 | 1, INF = 0x3f3f3f3f;
struct Info {
	int sum, pre, suf, mid;
	int preR, sufL, midL, midR;
	void init(int val, int pos) {
		sum = pre = suf = mid = val;
		preR = sufL = midL = midR = pos;
	}
	void update(Info const &lft, Info const &rht) {
		static int tmp;
		sum = lft.sum + rht.sum;
		tmp = lft.sum + rht.pre;
		if(lft.pre < tmp) {
			pre = tmp;
			preR = rht.preR;
		} else {
			pre = lft.pre;
			preR = lft.preR;
		}
		tmp = lft.suf + rht.sum;
		if(rht.suf < tmp) {
			suf = tmp;
			sufL = lft.sufL;
		} else {
			suf = rht.suf;
			sufL = rht.sufL;
		}
		tmp = lft.suf + rht.pre;
		if(lft.mid < tmp) {
			if(rht.mid < tmp) {
				mid = tmp;
				midL = lft.sufL;
				midR = rht.preR;
			} else {
				mid = rht.mid;
				midL = rht.midL;
				midR = rht.midR;
			}
		} else if(lft.mid < rht.mid) {
			mid = rht.mid;
			midL = rht.midL;
			midR = rht.midR;
		} else {
			mid = lft.mid;
			midL = lft.midL;
			midR = lft.midR;
		}
	}
} pool[maxn * 4 + maxd], *tail = pool;
struct Segment {
	bool rev;
	Info *info[2];
} seg[maxn << 1 | 1];
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
inline void seg_up(Segment &rt, Segment &lft, Segment &rht) {
	rt.info[rt.rev] -> update(*lft.info[lft.rev], *rht.info[rht.rev]);
	rt.info[!rt.rev] -> update(*lft.info[!lft.rev], *rht.info[!rht.rev]);
}
inline void seg_down(Segment &rt, Segment &lft, Segment &rht) {
	if(rt.rev) {
		rt.rev = 0;
		swap(rt.info[0], rt.info[1]);
		lft.rev = !lft.rev;
		rht.rev = !rht.rev;
	}
}
void seg_init(int L, int R) {
	int rt = seg_idx(L, R);
	seg[rt].rev = 0;
	seg[rt].info[0] = tail++;
	seg[rt].info[1] = tail++;
	if(L == R) {
		int v;
		scanf("%d", &v);
		seg[rt].info[seg[rt].rev] -> init(v, L);
		seg[rt].info[!seg[rt].rev] -> init(-v, L);
		return;
	}
	int M = (L + R) >> 1;
	seg_init(L, M);
	seg_init(M + 1, R);
	seg_up(seg[rt], seg[seg_idx(L, M)], seg[seg_idx(M + 1, R)]);
}
void seg_upd(int L, int R, int const &x, int const &v) {
	int rt = seg_idx(L, R);
	if(L == R) {
		seg[rt].info[seg[rt].rev] -> init(v, L);
		seg[rt].info[!seg[rt].rev] -> init(-v, L);
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	seg_down(seg[rt], seg[lch], seg[rch]);
	x <= M ? seg_upd(L, M, x, v) : seg_upd(M + 1, R, x, v);
	seg_up(seg[rt], seg[lch], seg[rch]);
}
void seg_rev(int L, int R, int const &qL, int const &qR) {
	int rt = seg_idx(L, R);
	if(qL <= L && R <= qR) {
		seg[rt].rev = !seg[rt].rev;
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	seg_down(seg[rt], seg[lch], seg[rch]);
	if(qL <= M)
		seg_rev(L, M, qL, qR);
	if(M < qR)
		seg_rev(M + 1, R, qL, qR);
	seg_up(seg[rt], seg[lch], seg[rch]);
}
Info *seg_que(int L, int R, int const &qL, int const &qR) {
	int rt = seg_idx(L, R);
	if(qL <= L && R <= qR)
		return seg[rt].info[seg[rt].rev];
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	seg_down(seg[rt], seg[lch], seg[rch]);
	Info *ret;
	if(qR <= M) {
		ret = seg_que(L, M, qL, qR);
	} else if(M < qL) {
		ret = seg_que(M + 1, R, qL, qR);
	} else {
		ret = tail++;
		ret -> update(*seg_que(L, M, qL, qR), *seg_que(M + 1, R, qL, qR));
	}
	seg_up(seg[rt], seg[lch], seg[rch]);
	return ret;
}
int main() {
	int n, m;
	scanf("%d", &n);
	seg_init(1, n);
	Info *pos = tail;
	scanf("%d", &m);
	while(m--) {
		int typ, x, y, z;
		scanf("%d%d%d", &typ, &x, &y);
		if(!typ) {
			seg_upd(1, n, x, y);
		} else {
			static int qL[maxk], qR[maxk];
			scanf("%d", &z);
			int res = 0;
			for(int i = 0; i < z; ++i) {
				Info const &tmp = *seg_que(1, n, x, y);
				tail = pos;
				if(tmp.mid <= 0) {
					z = i;
					break;
				}
				res += tmp.mid;
				qL[i] = tmp.midL;
				qR[i] = tmp.midR;
				seg_rev(1, n, qL[i], qR[i]);
			}
			printf("%d\n", res);
			for(int i = z - 1; i >= 0; --i)
				seg_rev(1, n, qL[i], qR[i]);
		}
	}
	return 0;
}
