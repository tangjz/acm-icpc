#include <stdio.h>
#include <algorithm>
const int maxn = 100001;
int n, a[maxn];
struct Segment {
	int val, tag;
} seg[maxn << 1 | 1];
inline int seg_idx(int L, int R)
{
	return (L + R) | (L < R);
}
void seg_down(int rt, int lch, int rch)
{
	if(!seg[rt].tag)
		return;
	seg[lch].val += seg[rt].tag;
	seg[lch].tag += seg[rt].tag;
	seg[rch].val += seg[rt].tag;
	seg[rch].tag += seg[rt].tag;
	seg[rt].tag = 0;
}
void seg_up(int rt, int lch, int rch)
{
	seg[rt].val = std::max(seg[lch].val, seg[rch].val);
}
void seg_upd(int L, int R, int x, int v)
{
	int rt = seg_idx(L, R);
	if(R <= x)
	{
		seg[rt].val += v;
		seg[rt].tag += v;
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	seg_down(rt, lch, rch);
	seg_upd(L, M, x, v);
	if(x > M)
		seg_upd(M + 1, R, x, v);
	seg_up(rt, lch, rch);
}
int seg_que(int L, int R)
{
	int rt = seg_idx(L, R);
	if(L == R)
		return L;
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R), ret;
	seg_down(rt, lch, rch);
	ret = seg[rch].val <= 0 ? seg_que(L, M) : seg_que(M + 1, R);
	seg_up(rt, lch, rch);
	return ret;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		int pos, typ;
		scanf("%d%d", &pos, &typ);
		if(typ == 1)
		{
			scanf("%d", a + pos);
			seg_upd(1, n, pos, 1);
		}
		else
			seg_upd(1, n, pos, -1);
		if(seg[seg_idx(1, n)].val <= 0)
			puts("-1");
		else
			printf("%d\n", a[seg_que(1, n)]);
	}
	return 0;
}
