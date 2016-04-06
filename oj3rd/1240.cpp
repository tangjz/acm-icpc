#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;
typedef long long LL;
int n, m, p, t, q_tot, que[maxn << 1], p_tot;
LL ans;
struct Square
{
	int x1, y1, x2, y2;
} a[maxn];
struct Segment
{
	int typ, y, x1, x2;
	bool operator < (const Segment &t) const
	{
		return y < t.y || y == t.y && typ < t.typ;
	}
} pp[maxn << 1];
struct SegTree
{
	int cnt, len;
} seg[maxn << 2];
inline int idx(int L, int R)
{
	return L + R | L != R;
}
void upd(int L, int R, int l, int r, int sgn)
{
	int o = idx(L, R), M = L + R >> 1, lch = idx(L, M), rch = idx(M + 1, R);
	if(l <= L && R <= r)
	{
		seg[o].cnt += sgn;
		seg[o].len = seg[o].cnt ? que[R + 1] - que[L] : (L == R ? 0 : seg[lch].len + seg[rch].len);
		return;
	}
	if(l <= M)
		upd(L, M, l, r, sgn);
	if(r > M)
		upd(M + 1, R, l, r, sgn);
	seg[o].len = seg[o].cnt ? que[R + 1] - que[L] : seg[lch].len + seg[rch].len;
}
LL solve()
{
	LL ret = 0;
	q_tot = p_tot = 0;
	for(int i = 0; i <= p; ++i)
	{
		int x1 = a[i].x1, y1 = a[i].y1, x2 = a[i].x2, y2 = a[i].y2;
		if(x1 <= 0)
			x1 = 1;
		if(y1 <= 0)
			y1 = 1;
		if(x2 > n)
			x2 = n;
		if(y2 > m)
			y2 = m;
		if(x1 > x2 || y1 > y2)
			continue;
		que[q_tot++] = x1;
		que[q_tot++] = x2 + 1;
		pp[p_tot++] = (Segment){1, y1, x1, x2 + 1};
		pp[p_tot++] = (Segment){-1, y2 + 1, x1, x2 + 1};
	}
	sort(que, que + q_tot);
	q_tot = unique(que, que + q_tot) - que;
	sort(pp, pp + p_tot);
	memset(seg, 0, sizeof seg);
	for(int i = 0; i < p_tot - 1; ++i)
	{
		int L = lower_bound(que, que + q_tot, pp[i].x1) - que, R = lower_bound(que, que + q_tot, pp[i].x2) - que;
		upd(0, q_tot - 2, L, R - 1, pp[i].typ);
		ret += (LL)(pp[i + 1].y - pp[i].y) * seg[idx(0, q_tot - 2)].len;
	}
	return ret;
}
int main()
{
	while(scanf("%d%d%d%d", &n, &m, &p, &t) == 4)
	{
		for(int i = 0; i < p; ++i)
		{
			scanf("%d%d%d%d", &a[i].x1, &a[i].y1, &a[i].x2, &a[i].y2);
			a[i].x2 += t - 1;
		}
		a[p] = (Square){0, 1, t - 1, m};
		ans = (LL)n * m - solve();
		if(t > 1)
		{
			for(int i = 0; i < p; ++i)
			{
				a[i].x2 -= t - 1;
				a[i].y2 += t - 1;
			}
			a[p] = (Square){1, 0, n, t - 1};
			ans += (LL)n * m - solve();
		}
		printf("%lld\n", ans);
	}
	return 0;
}
