#include <stdio.h>
#include <cstring>
#include <algorithm>
typedef unsigned int UL;
typedef unsigned long long ULL;
const int maxn = 100000, mod = 2017, maxs = ((mod - 1) >> 6) + 1, maxp = 1 << 16, maxc = 15, maxl = 6;
// Graph
int nxt[mod], nxt2[mod][maxl | 1], sys_tim, tim[mod];
int cir_cnt, cir_fir[maxc], cir_pos[maxc + 2];
int idx_tot, idx[mod];
void pfs(int u)
{
	tim[u] = sys_tim;
	if(!tim[nxt[u]])
		pfs(nxt[u]);
	else if(tim[nxt[u]] == sys_tim)
		cir_fir[++cir_cnt] = u;
}
// Bitset
int lbt[maxp | 1], cnt[maxp | 1];
inline int popcount(UL x)
{
	return cnt[x >> 16] + cnt[x & 65535];
}
inline int popcount(ULL x)
{
	return popcount((UL)(x >> 32)) + popcount((UL)x);
}
inline void bit_rotate(ULL &x, int l, int r, int d) // [l, r) bits in x rotate left d unit
{
	register int len = r - l;
	if(len > 2)
		while(d >= len)
			d -= len;
	else
		d &= len - 1;
	if(!d)
		return;
	register ULL val = (x >> l) & ((1ULL << len) - 1); // len = 1, 2, 3, 6
	x ^= ((val ^ ((val << d | val >> (len - d)) & ((1ULL << len) - 1))) << l);
}
struct Bitset
{
	ULL data[maxs | 1];
	void reset()
	{
		memset(data, 0, maxs * sizeof(ULL));
	}
	void reset(int const &x)
	{
		data[x >> 6] &= ~(1ULL << (x & 63));
	}
	void set(int const &x)
	{
		data[x >> 6] |= 1ULL << (x & 63);
	}
	bool test(int const &x) const
	{
		return (data[x >> 6] >> (x & 63)) & 1;
	}
	void operator = (Bitset const &src)
	{
		memcpy(data, src.data, sizeof data);
	}
	void operator |= (Bitset const &src)
	{
		register int i;
		for(i = 0; i < maxs; ++i)
			data[i] |= src.data[i];
	}
	int popcount() const
	{
		register int ret = 0, i;
		for(i = 0; i < maxs; ++i)
			ret += ::popcount(data[i]);
		return ret;
	}
} ;
// Segment Tree
struct Segment
{
	int delta, eqv;
	bool incir;
	Bitset mask;
} seg[maxn << 1 | 1];
inline int seg_idx(int L, int R)
{
	return (L + R) | (L < R);
}
inline void mask_rotate(ULL &mask, int delta)
{
	register int i;
	for(i = 1; i <= cir_cnt; ++i)
		bit_rotate(mask, cir_pos[i], cir_pos[i + 1], delta);
}
inline void push_up(int rt, int lch, int rch)
{
	seg[rt].eqv = seg[lch].eqv == seg[rch].eqv ? seg[lch].eqv : -1;
	seg[rt].incir = seg[lch].incir && seg[rch].incir;
	seg[rt].mask = seg[lch].mask;
	seg[rt].mask |= seg[rch].mask;
}
void build(int L, int R)
{
	int rt = seg_idx(L, R);
	seg[rt].delta = 0;
	if(L == R)
	{
		int &val = seg[rt].eqv;
		scanf("%d", &val);
		seg[rt].incir = !tim[val];
		seg[rt].mask.reset();
		seg[rt].mask.set(idx[val]);
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	build(L, M);
	build(M + 1, R);
	push_up(rt, lch, rch);
}
inline void push_down(int rt, int lch, int rch)
{
	if(seg[rt].eqv != -1)
	{
		seg[rt].delta = 0;
		if(seg[lch].eqv != seg[rt].eqv)
			seg[lch] = seg[rt];
		if(seg[rch].eqv != seg[rt].eqv)
			seg[rch] = seg[rt];
	}
	else if(seg[rt].delta) // seg[rt].incir = 1
	{
		int &delta = seg[rt].delta;
		if(seg[lch].eqv != -1)
		{
			int &val = seg[lch].eqv;
			seg[lch].mask.reset(idx[val]);
			val = nxt2[val][delta];
			seg[lch].mask.set(idx[val]);
			seg[lch].incir = !tim[val];
		}
		else
		{
			(seg[lch].delta += delta) >= maxl && (seg[lch].delta -= maxl);
			mask_rotate(seg[lch].mask.data[0], delta);
		}
		if(seg[rch].eqv != -1)
		{
			int &val = seg[rch].eqv;
			seg[rch].mask.reset(idx[val]);
			val = nxt2[val][delta];
			seg[rch].mask.set(idx[val]);
			seg[rch].incir = !tim[val];
		}
		else
		{
			(seg[rch].delta += delta) >= maxl && (seg[rch].delta -= maxl);
			mask_rotate(seg[rch].mask.data[0], delta);
		}
		delta = 0;
	}
}
void update_sqr(int L, int R, int l, int r)
{
	int rt = seg_idx(L, R);
	if(l <= L && R <= r)
	{
		if(seg[rt].eqv != -1)
		{
			int &val = seg[rt].eqv;
			seg[rt].mask.reset(idx[val]);
			val = nxt[val];
			seg[rt].mask.set(idx[val]);
			seg[rt].incir = !tim[val];
			return;
		}
		else if(seg[rt].incir)
		{
			(++seg[rt].delta) >= maxl && (seg[rt].delta -= maxl);
			mask_rotate(seg[rt].mask.data[0], 1);
			return;
		}
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	push_down(rt, lch, rch);
	if(l <= M)
		update_sqr(L, M, l, r);
	if(r > M)
		update_sqr(M + 1, R, l, r);
	push_up(rt, lch, rch);
}
void update_rep(int L, int R, int l, int r, int x)
{
	int rt = seg_idx(L, R);
	if(l <= L && R <= r)
	{
		seg[rt].eqv = x;
		seg[rt].delta = 0;
		seg[rt].incir = !tim[x];
		seg[rt].mask.reset();
		seg[rt].mask.set(idx[x]);
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	push_down(rt, lch, rch);
	if(l <= M)
		update_rep(L, M, l, r, x);
	if(r > M)
		update_rep(M + 1, R, l, r, x);
	push_up(rt, lch, rch);
}
Bitset result;
void query(int L, int R, int l, int r)
{
	int rt = seg_idx(L, R);
	if(l <= L && R <= r)
	{
		result |= seg[rt].mask;
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	push_down(rt, lch, rch);
	if(l <= M)
		query(L, M, l, r);
	if(r > M)
		query(M + 1, R, l, r);
	push_up(rt, lch, rch);
}
int main()
{
	register int i, j, t, n, m, s, x;
	// Graph Init
	for(i = 0; i < mod; ++i)
		nxt[i] = i * i % mod;
	for(i = 0; i < mod; ++i)
	{
		nxt2[i][0] = i;
		for(j = 1; j < maxl; ++j)
			nxt2[i][j] = nxt[nxt2[i][j - 1]];
	}
	for(i = 0; i < mod; ++i)
		if(!tim[i])
		{
			++sys_tim;
			pfs(i);
		}
	for(cir_pos[i = 1] = idx_tot; i <= cir_cnt; cir_pos[++i] = idx_tot)
		for(cir_pos[i] = idx_tot, j = cir_fir[i]; tim[j]; j = nxt[j])
		{
			tim[j] = 0;
			idx[j] = idx_tot++;
		}
	for(i = 0; i < mod; ++i)
		if(tim[i])
			idx[i] = idx_tot++;
	// Bitset Init
	lbt[0] = -1;
	for(i = 1; i < maxp; ++i)
		if(i & 1)
		{
			lbt[i] = 0;
			cnt[i] = cnt[i >> 1] + 1;
		}
		else
		{
			lbt[i] = lbt[i >> 1] + 1;
			cnt[i] = cnt[i >> 1];
		}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		build(0, n - 1);
		while(m--)
		{
			scanf("%d%d%d", &s, &i, &j);
			--i, --j;
			if(s == 1)
				update_sqr(0, n - 1, i, j);
			else if(s == 2)
			{
				scanf("%d", &x);
				update_rep(0, n - 1, i, j, x);
			}
			else
			{
				result.reset();
				query(0, n - 1, i, j);
				printf("%d\n", result.popcount());
			}
		}
	}
	return 0;
}
