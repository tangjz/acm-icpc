#include <stdio.h>
#include <algorithm>
#include <functional>
const int maxn = 300001;
int n, a[maxn], b[maxn];
long long ans;
struct Segment {
	int cnt, val, tag;
} seg[(maxn - 1) << 1 | 1];
inline int seg_idx(int L, int R)
{
	return (L + R) | (L < R);
}
inline void seg_up(int rt, int lch, int rch)
{
	if(seg[lch].val < seg[rch].val)
		seg[rt] = seg[lch];
	else if(seg[lch].val > seg[rch].val)
		seg[rt] = seg[rch];
	else
		seg[rt] = (Segment){seg[lch].cnt + seg[rch].cnt, seg[lch].val};
	seg[rt].tag = 0;
}
inline void seg_down(int rt, int lch, int rch)
{
	if(seg[rt].tag)
	{
		int &tag = seg[rt].tag;
		seg[lch].val += tag;
		seg[lch].tag += tag;
		seg[rch].val += tag;
		seg[rch].tag += tag;
		tag = 0;
	}
}
void seg_init(int L, int R)
{
	int rt = seg_idx(L, R);
	if(L == R)
	{
		seg[rt].cnt = 1;
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	seg_init(L, M);
	seg_init(M + 1, R);
	seg_up(rt, lch, rch);
}
void seg_upd(int L, int R, int l, int r, int v)
{
	int rt = seg_idx(L, R);
	if(l <= L && R <= r)
	{
		seg[rt].val += v;
		seg[rt].tag += v;
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	seg_down(rt, lch, rch);
	if(l <= M)
		seg_upd(L, M, l, r, v);
	if(M < r)
		seg_upd(M + 1, R, l, r, v);
	seg_up(rt, lch, rch);
}
int seg_que(int L, int R, int l, int r) // make sure seg[rt].val < 2
{
	int rt = seg_idx(L, R);
	if(l <= L && R <= r)
		return seg[rt].val == 1 ? seg[rt].cnt : 0;
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R), ret = 0;
	seg_down(rt, lch, rch);
	if(l <= M && seg[lch].val < 2)
		ret += seg_que(L, M, l, r);
	if(M < r && seg[rch].val < 2)
		ret += seg_que(M + 1, R, l, r);
	seg_up(rt, lch, rch);
	return ret;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		a[x] = y;
		b[y] = x;
	}
	seg_init(1, n);
	for(int i = 1; i <= n; ++i)
	{
		int v = a[i], sz = 2, pos[5] = {i, 0};
		if(v > 1 && b[v - 1] < i)
			pos[sz++] = b[v - 1];
		if(v < n && b[v + 1] < i)
			pos[sz++] = b[v + 1];
		std::sort(pos, pos + sz, std::greater<int>());
		seg_upd(1, n, pos[1] + 1, pos[0], 1);
		if(sz == 4)
			seg_upd(1, n, pos[3] + 1, pos[2], -1);
		ans += seg_que(1, n, 1, i);
	}
	printf("%lld\n", ans);
	return 0;
}
