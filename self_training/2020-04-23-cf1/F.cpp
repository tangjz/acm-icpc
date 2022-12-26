#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxd = 18 * 3 + 1;
const int mod0 = (int)1e9 + 7, seed0 = (int)1e5 + 3; // seed > maxn && seed is a primitive root and prime
const int mod1 = (int)1e9 + 403, seed1 = (int)1e5 + 19;
inline int mod_add(int x, int y, int mod) {
	return (x += y) < mod ? x : (x - mod);
}
inline int mod_sub(int x, int y, int mod) {
	return (x -= y) < 0 ? (x + mod) : x;
}
inline int mod_mul(int x, int y, int mod) {
	return (LL)x * y % mod;
}
inline int mod_inv(int x, int mod) {
	int y = mod, u = 1, v = 0;
	while(x > 0) {
		int q = y / x;
		tie(x, y) = make_pair(y - q * x, x);
		tie(u, v) = make_pair(v - q * u, u);
	}
	assert(y == 1);
	return v < 0 ? (v + mod) : v;
}
int pw0[maxn], pw1[maxn], ivs0[maxn], ivs1[maxn];
struct Hash {
	int len, h0, h1;
	bool operator == (Hash const &t) const {
		return len == t.len && h0 == t.h0 && h1 == t.h1;
	}
	Hash operator + (Hash const &t) const {
		return (Hash){
			len + t.len,
			mod_add(mod_mul(h0, pw0[t.len], mod0), t.h0, mod0),
			mod_add(mod_mul(h1, pw1[t.len], mod1), t.h1, mod1)
		};
	}
	Hash operator - (Hash const &t) const {
		assert(len >= t.len);
		return (Hash){
			len - t.len,
			mod_mul(mod_sub(h0, t.h0, mod0), ivs0[t.len], mod0),
			mod_mul(mod_sub(h1, t.h1, mod1), ivs1[t.len], mod1)
		};
	}
} O = {};
void init_hash(int len) {
	auto prepare = [&](int arr[], int val, int mod) {
		arr[0] = 1;
		for(int i = 1; i <= len; ++i)
			arr[i] = mod_mul(arr[i - 1], val, mod);
	};
	prepare(pw0, seed0, mod0);
	prepare(pw1, seed1, mod1);
	prepare(ivs0, mod_inv(seed0, mod0), mod0);
	prepare(ivs1, mod_inv(seed1, mod1), mod1);
}
struct Segment {
	bool bad;
	Hash hL, hR;
	void assign(int v) {
		assert(v != 0);
		bad = 0;
		hL = v > 0 ? O : (Hash){1, -v, -v};
		hR = v < 0 ? O : (Hash){1, v, v};
	}
} seg[maxn << 1 | 1];
inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}
Hash seg_left_hash(int L, int R, int len) {
	assert(len > 0);
	int rt = seg_idx(L, R);
	if(seg[rt].hL.len == len)
		return seg[rt].hL;
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	int lenL = seg[lch].hL.len;
	if(len <= lenL)
		return seg_left_hash(L, M, len);
	return (seg_left_hash(M + 1, R, len - lenL + seg[lch].hR.len) - seg[lch].hR) + seg[lch].hL;
}
Hash seg_right_hash(int L, int R, int len) {
	assert(len > 0);
	int rt = seg_idx(L, R);
	if(seg[rt].hR.len == len)
		return seg[rt].hR;
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	int lenR = seg[rch].hR.len;
	if(len <= lenR)
		return seg_right_hash(M + 1, R, len);
	return (seg_right_hash(L, M, len - lenR + seg[rch].hL.len) - seg[rch].hL) + seg[rch].hR;
}
inline void seg_merge(int L, int R) {
	int rt = seg_idx(L, R);
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	seg[rt].bad = 1;
	if(seg[lch].bad || seg[rch].bad)
		return;
	int lenL = seg[lch].hR.len, lenR = seg[rch].hL.len;
	int com = min(lenL, lenR);
	if(com > 0 && !(seg_right_hash(L, M, com) == seg_left_hash(M + 1, R, com)))
		return;
	seg[rt].bad = 0;
	seg[rt].hL = com < lenR ? (seg[rch].hL - seg[lch].hR) + seg[lch].hL : seg[lch].hL;
	seg[rt].hR = com < lenL ? (seg[lch].hR - seg[rch].hL) + seg[rch].hR : seg[rch].hR;
}
void seg_build(int L, int R) {
	if(L < R) {
		int M = (L + R) >> 1;
		seg_build(L, M);
		seg_build(M + 1, R);
		seg_merge(L, R);
	} else {
		static int v;
		scanf("%d", &v);
		seg[seg_idx(L, R)].assign(v);
	}
}
void seg_upd(int L, int R, int x, int v) {
	if(L < R) {
		int M = (L + R) >> 1;
		if(x <= M) {
			seg_upd(L, M, x, v);
		} else {
			seg_upd(M + 1, R, x, v);
		}
		seg_merge(L, R);
	} else {
		seg[seg_idx(L, R)].assign(v);
	}
}
int tot;
pair<int, int> que[maxd];
void seg_que(int L, int R, int l, int r) {
	if(l <= L && R <= r) {
		que[tot++] = make_pair(L, R);
	} else {
		int M = (L + R) >> 1;
		if(l <= M)
			seg_que(L, M, l, r);
		if(r > M)
			seg_que(M + 1, R, l, r);
	}
}
int main() {
	int n, m;
	scanf("%d%*d", &n);
	init_hash(n);
	seg_build(1, n);
	scanf("%d", &m);
	while(m--) {
		int typ, x, y;
		scanf("%d%d%d", &typ, &x, &y);
		if(typ == 1) {
			seg_upd(1, n, x, y);
		} else {
			tot = 0;
			seg_que(1, n, x, y);
			bool chk = 1;
			int rem = 0;
			static pair<int, Hash> stk[maxd];
			while(tot--) {
				int uL, uR;
				tie(uL, uR) = que[tot];
				int u = seg_idx(uL, uR);
				if(seg[u].bad) {
					chk = 0;
					break;
				}
				Hash okU = O;
				while(okU.len < seg[u].hR.len && rem > 0) {
					int id;
					Hash okV;
					tie(id, okV) = stk[--rem];
					int vL, vR;
					tie(vL, vR) = que[id];
					int v = seg_idx(vL, vR);
					int com = min(seg[u].hR.len - okU.len, seg[v].hL.len - okV.len);
					Hash nxtU = seg_right_hash(uL, uR, len + okU.len);
					Hash nxtV = seg_left_hash(vL, vR, len + okV.len);
					if((nxtU - okU) != (nxtV - okV))
						break;
					okU = nxtU;
					if(nxtV.len < seg[v].hL.len)
						stk[rem++] = make_pair(id, nxtV);
				}
				if(okU.len < seg[u].hR.len) {
					chk = 0;
					break;
				}
				if(seg[u].hL.len > 0)
					stk[rem++] = make_pair(tot, O);
			}
			chk &= !rem;
			puts(chk ? "Yes" : "No");
		}
	}
	return 0;
}