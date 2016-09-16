#include <stdio.h>
#include <cstring>
#include <algorithm>
const int maxn = 50001;
int t, n, rN, cN, m, tot, que[maxn << 1], ans;
struct Event
{
	int x, y1, y2, val;
	bool operator < (const Event &t) const
	{
		return x < t.x;
	}
} e[maxn << 1];
struct Segment
{
	int val, tag;
} seg[maxn << 2];
inline int seg_idx(int L, int R)
{
	return L + R | L < R;
}
void upd(int L, int R, int l, int r, int v)
{
	int rt = seg_idx(L, R);
	if(l <= L && R <= r)
	{
		seg[rt].val += v;
		seg[rt].tag += v;
		return;
	}
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(seg[rt].tag)
	{
		seg[lch].val += seg[rt].tag;
		seg[lch].tag += seg[rt].tag;
		seg[rch].val += seg[rt].tag;
		seg[rch].tag += seg[rt].tag;
		seg[rt].tag = 0;
	}
	if(l <= M)
		upd(L, M, l, r, v);
	if(r > M)
		upd(M + 1, R, l, r, v);
	seg[rt].val = std::max(seg[lch].val, seg[rch].val);
}
int main()
{
	scanf("%d%d%d", &n, &rN, &cN);
	while(n--)
	{
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		e[m++] = (Event){x, y, y + cN + 1, w};
		e[m++] = (Event){x + rN + 1, y, y + cN + 1, -w};
		que[tot++] = y;
		que[tot++] = y + cN + 1;
	}
	std::sort(e, e + m);
	std::sort(que, que + tot);
	tot = std::unique(que, que + tot) - que;
	int rt = seg_idx(0, tot - 1);
	for(int i = 0, j = 0; i < m; i = j)
	{
		for( ; j < m && e[i].x == e[j].x; ++j)
		{
			e[j].y1 = std::lower_bound(que, que + tot, e[j].y1) - que;
			e[j].y2 = std::lower_bound(que, que + tot, e[j].y2) - que;
			upd(0, tot - 1, e[j].y1, e[j].y2 - 1, e[j].val);
		}
		if(ans < seg[rt].val)
			ans = seg[rt].val;
	}
	printf("%d\n", ans);
	return 0;
}
