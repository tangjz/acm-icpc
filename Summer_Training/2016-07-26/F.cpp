#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 100001;
int t, n, rN, cN, m, tot, que[maxn << 1], s[maxn << 1], ans;
struct Event
{
	int x, y1, y2, sgn;
	bool operator < (const Event &t) const
	{
		return x < t.x;
	}
} e[maxn << 1];
struct Segment
{
	int vis, val;
} seg[maxn << 2];
inline int seg_idx(int L, int R)
{
	return L + R | L < R;
}
void build(int L, int R)
{
	int rt = seg_idx(L, R);
	if(L == R)
	{
		seg[rt].vis = 0;
		seg[rt].val = s[L];
		return;
	}
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	build(L, M);
	build(M + 1, R);
	seg[rt].vis = 0;
	seg[rt].val = std::max(seg[lch].val, seg[rch].val);
}
void upd(int L, int R, int l, int r, int v)
{
	int rt = seg_idx(L, R);
	if(l <= L && R <= r)
	{
		if((seg[rt].vis += v))
			seg[rt].val = 0;
		else if(L == R)
			seg[rt].val = s[L];
		else
		{
			int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
			seg[rt].val = std::max(seg[lch].val, seg[rch].val);
		}
		return;
	}
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(l <= M)
		upd(L, M, l, r, v);
	if(r > M)
		upd(M + 1, R, l, r, v);
	seg[rt].val = seg[rt].vis ? 0 : std::max(seg[lch].val, seg[rch].val);
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		m = tot = ans = 0;
		scanf("%d%d%d", &n, &rN, &cN);
		while(n--)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			e[m++] = (Event){x, y, y + cN, 1};
			e[m++] = (Event){x + rN, y, y + cN, -1};
			que[tot++] = y;
			que[tot++] = y + cN;
		}
		std::sort(e, e + m);
		std::sort(que, que + tot);
		tot = std::unique(que, que + tot) - que;
		memset(s, 0, tot * sizeof(int));
		for(int i = 0; i < m; ++i)
		{
			e[i].y1 = std::lower_bound(que, que + tot, e[i].y1) - que;
			e[i].y2 = std::lower_bound(que, que + tot, e[i].y2) - que;
			if(e[i].sgn > 0)
			{
				++s[e[i].y1];
				--s[e[i].y2];
			}
		}
		for(int i = 1; i < tot; ++i)
			s[i] += s[i - 1];
		build(0, tot - 1);
		int c = 0, rt = seg_idx(0, tot - 1);
		for(int i = 0, j = 0; i < m; i = j)
		{
			for( ; j < m && e[i].x == e[j].x; ++j)
			{
				upd(0, tot - 1, e[j].y1, e[j].y2 - 1, e[j].sgn);
				c += e[j].sgn;
			}
			if(ans < c + seg[rt].val)
				ans = c + seg[rt].val;
		}
		printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}
