#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
int t, n, m, a[maxn];
struct Segment {
	int sum, ass;
	LL max, add;
	void set(int size, int value) {
		sum = size;
		ass = max = value;
		add = 0;
	}
	void inc(LL value) {
		max += value;
		add += value;
	}
} segF[maxn << 1 | 1], segB[maxn << 1 | 1], *seg;
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
inline void seg_down(int L, int R) {
	int M = (L + R) >> 1, rt = seg_idx(L, R), lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(seg[rt].ass) {
		seg[lch].set(M - L + 1, seg[rt].ass);
		seg[rch].set(R - M, seg[rt].ass);
		seg[rt].ass = 0;
	}
	if(seg[rt].add) {
		seg[lch].inc(seg[rt].add);
		seg[rch].inc(seg[rt].add);
		seg[rt].add = 0;
	}
}
int seg_que(int L, int R, LL v) {
	int rt = seg_idx(L, R);
	if(seg[rt].max < v)
		return 0;
	if(L == R)
		return 1;
	int M = (L + R) >> 1, lch = seg_idx(L, M);
	seg_down(L, R);
	return seg[lch].max < v ? seg_que(M + 1, R, v) : seg_que(L, M, v) + seg[rt].sum - seg[lch].sum;
}
inline void seg_up(int L, int R) {
	int M = (L + R) >> 1, rt = seg_idx(L, R), lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	seg[rt].max = max(seg[lch].max, seg[rch].max);
	seg[rt].sum = seg[lch].sum + seg_que(M + 1, R, seg[lch].max);
}
void seg_init(int L, int R) {
	int rt = seg_idx(L, R);
	if(L == R) {
		seg[rt].set(1, a[L]);
		return;
	}
	int M = (L + R) >> 1;
	seg_init(L, M);
	seg_init(M + 1, R);
	seg_up(L, R);
	seg[rt].ass = seg[rt].add = 0;
}
void seg_ass(int L, int R, int l, int r, int v) {
	if(l <= L && R <= r) {
		seg[seg_idx(L, R)].set(R - L + 1, v);
		return;
	}
	int M = (L + R) >> 1;
	seg_down(L, R);
	if(l <= M)
		seg_ass(L, M, l, r, v);
	if(M < r)
		seg_ass(M + 1, R, l, r, v);
	seg_up(L, R);
}
void seg_add(int L, int R, int l, int r, int v) {
	if(l <= L && R <= r) {
		seg[seg_idx(L, R)].inc(v);
		return;
	}
	int M = (L + R) >> 1;
	seg_down(L, R);
	if(l <= M)
		seg_add(L, M, l, r, v);
	if(M < r)
		seg_add(M + 1, R, l, r, v);
	seg_up(L, R);
}
inline int seg_find(int L, int R, LL v) {
	while(L < R) {
		int M = (L + R) >> 1, lch = seg_idx(L, M);
		seg_down(L, R);
		if(seg[lch].max > v) {
			R = M;
		} else {
			L = M + 1;
		}
	}
	return L;
}
int seg_find(int L, int R, int l, int r, LL v) {
	int rt = seg_idx(L, R);
	if(l <= L && R <= r)
		return seg[rt].max > v ? seg_find(L, R, v) : maxn;
	int M = (L + R) >> 1, ret = maxn;
	seg_down(L, R);
	if(l <= M && ret == maxn)
		ret = seg_find(L, M, l, r, v);
	if(M < r && ret == maxn)
		ret = seg_find(M + 1, R, l, r, v);
	return ret;
}
int seg_que(int L, int R, int l, int r, LL &v) {
	if(l <= L && R <= r) {
		int ret = seg_que(L, R, v);
		v = max(v, seg[seg_idx(L, R)].max);
		return ret;
	}
	int M = (L + R) >> 1, ret = 0;
	seg_down(L, R);
	if(l <= M)
		ret += seg_que(L, M, l, r, v);
	if(M < r)
		ret += seg_que(M + 1, R, l, r, v);
	return ret;
}
void seg_chk(int L, int R, int l, int r, LL &v) {
	if(l <= L && R <= r) {
		v = max(v, seg[seg_idx(L, R)].max);
		return;
	}
	int M = (L + R) >> 1;
	seg_down(L, R);
	if(l <= M)
		seg_chk(L, M, l, r, v);
	if(M < r)
		seg_chk(M + 1, R, l, r, v);
}
inline int solve(int x, int l, int r) {
	int pos = seg_find(1, n, x, x, 0);
	LL val = seg[seg_idx(pos, pos)].max;
	pos = pos < n ? seg_find(1, n, pos + 1, n, val) : maxn;
	val = pos <= n ? seg[seg_idx(pos, pos)].max : 0;
	if(pos > r)
		return r - l + 1;
	if(pos < l) {
		seg_chk(1, n, pos, l - 1, val);
		pos = l;
	}
	return pos - l + seg_que(1, n, pos, r, val);
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		seg = segF;
		seg_init(1, n);
		reverse(a + 1, a + n + 1);
		seg = segB;
		seg_init(1, n);
		while(m--) {
			int typ, L, R, x;
			scanf("%d%d%d%d", &typ, &L, &R, &x);
			if(typ <= 2) {
				auto seg_upd = typ < 2 ? seg_add : seg_ass;
				seg = segF;
				seg_upd(1, n, L, R, x);
				tie(L, R) = make_pair(n - R + 1, n - L + 1);
				seg = segB;
				seg_upd(1, n, L, R, x);
			} else {
				int ans = L <= x && x <= R;
				if(x < R) {
					seg = segF;
					ans += solve(x, max(L, x + 1), R);
				}
				if(x > L) {
					tie(L, R, x) = make_tuple(n - R + 1, n - L + 1, n - x + 1);
					seg = segB;
					ans += solve(x, max(L, x + 1), R);
				}
				printf("%d\n", ans);
			}
		}
	}
	return 0;
}
