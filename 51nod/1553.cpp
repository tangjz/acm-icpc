#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = (int)1e5 + 1, mod[2] = {(int)1e9 + 7, (int)1e9 + 9};
int n, m, q, tag[maxn << 1 | 1];
struct Hash {
	int val[2];
	bool operator == (Hash const &t) const {
		return val[0] == t.val[0] && val[1] == t.val[1];
	}
	Hash operator + (Hash const &t) const {
		int res[2] = {val[0] + t.val[0], val[1] + t.val[1]};
		return (Hash){{res[0] < mod[0] ? res[0] : res[0] - mod[0], res[1] < mod[1] ? res[1] : res[1] - mod[1]}};
	}
	Hash operator * (Hash const &t) const {
		return (Hash){{(int)((LL)val[0] * t.val[0] % mod[0]), (int)((LL)val[1] * t.val[1] % mod[1])}};
	}
} pw[maxn], sum[maxn], seg[maxn << 1 | 1];
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
int seg_build(int L, int R) {
	int rt = seg_idx(L, R);
	if(L == R) {
		int v;
		scanf("%1d", &v);
		++v;
		seg[rt] = (Hash){{v, v}};
	} else {
		int M = (L + R) >> 1, lch = seg_build(L, M), rch = seg_build(M + 1, R);
		seg[rt] = seg[lch] * pw[R - M] + seg[rch];
	}
	return rt;
}
void seg_upd(int L, int R, int l, int r, int v) {
	int rt = seg_idx(L, R);
	if(l <= L && R <= r) {
		tag[rt] = v;
		seg[rt] = sum[R - L + 1] * (Hash){{v, v}};
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(tag[rt]) {
		tag[lch] = tag[rt];
		seg[lch] = sum[M - L + 1] * (Hash){{tag[rt], tag[rt]}};
		tag[rch] = tag[rt];
		seg[rch] = sum[R - M] * (Hash){{tag[rt], tag[rt]}};
		tag[rt] = 0;
	}
	if(l <= M)
		seg_upd(L, M, l, r, v);
	if(M < r)
		seg_upd(M + 1, R, l, r, v);
	seg[rt] = seg[lch] * pw[R - M] + seg[rch];
}
Hash seg_que(int L, int R, int l, int r) {
	int rt = seg_idx(L, R);
	if(l <= L && R <= r)
		return seg[rt];
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(tag[rt]) {
		tag[lch] = tag[rt];
		seg[lch] = sum[M - L + 1] * (Hash){{tag[rt], tag[rt]}};
		tag[rch] = tag[rt];
		seg[rch] = sum[R - M] * (Hash){{tag[rt], tag[rt]}};
		tag[rt] = 0;
	}
	int len = 0;
	Hash ret = (Hash){{0, 0}};
	if(l <= M) {
		int adt = std::min(M, r) - std::max(L, l) + 1;
		len += adt;
		ret = ret * pw[adt] + seg_que(L, M, l, r);
	}
	if(M < r) {
		int adt = std::min(R, r) - std::max(M, l - 1);
		len += adt;
		ret = ret * pw[adt] + seg_que(M + 1, R, l, r);
	}
	seg[rt] = seg[lch] * pw[R - M] + seg[rch];
	return ret;
}
int main() {
	scanf("%d%d%d", &n, &m, &q);
	pw[0] = (Hash){{1, 1}};
	for(int i = 1; i <= n; ++i) {
		pw[i] = pw[i - 1] * (Hash){{13, 13}};
		sum[i] = sum[i - 1] + pw[i - 1];
	}
	seg_build(1, n);
	for(m += q; m--; ) {
		int typ, L, R, v;
		scanf("%d%d%d%d", &typ, &L, &R, &v);
		if(typ == 1) {
			seg_upd(1, n, L, R, ++v);
		} else {
			Hash lft = L <= R - v ? seg_que(1, n, L, R - v) : (Hash){{0, 0}};
			Hash rht = L + v <= R ? seg_que(1, n, L + v, R) : (Hash){{0, 0}};
			puts(lft == rht ? "YES" : "NO");
		}
	}
	return 0;
}
