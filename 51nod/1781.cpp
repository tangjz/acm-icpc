#include <stdio.h>
#include <algorithm>
typedef long long LL;
typedef std::pair<LL, LL> Info;
const int maxn = 100003;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
int n, m, tot, que[maxn];
struct Funnel {
	int L, M, R, C;
	void read() {
		scanf("%d%d%d%d", &L, &R, &M, &C);
	}
} a[maxn];
Info seg[maxn << 1 | 1];
inline void upd(LL &x, LL y)
{
	x > y && (x = y);
}
inline void upd(Info &x, Info y)
{
	upd(x.first, y.first);
	upd(x.second, y.second);
}
inline int seg_idx(int L, int R)
{
	return (L + R) | (L < R);
}
void seg_init(int L, int R)
{
	seg[seg_idx(L, R)] = (Info){INF, INF};
	if(L == R)
		return;
	int M = (L + R) >> 1;
	seg_init(L, M);
	seg_init(M + 1, R);
}
void seg_upd(int L, int R, int x, Info v)
{
	while(L < R)
	{
		upd(seg[seg_idx(L, R)], v);
		int M = (L + R) >> 1;
		if(x <= M)
			R = M;
		else
			L = M + 1;
	}
	upd(seg[seg_idx(L, R)], v);
}
Info seg_que(int L, int R, int l, int r)
{
	if(l <= L && R <= r)
		return seg[seg_idx(L, R)];
	int M = (L + R) >> 1;
	if(r <= M)
		return seg_que(L, M, l, r);
	if(M < l)
		return seg_que(M + 1, R, l, r);
	Info ret = seg_que(L, M, l, r);
	upd(ret, seg_que(M + 1, R, l, r));
	return ret;
}
int main()
{
	scanf("%d%d", &n, &m);
	que[tot++] = 1;
	for(int i = 0; i < n; ++i)
	{
		a[i].read();
		que[tot++] = a[i].M;
	}
	que[tot++] = m;
	std::sort(que, que + tot);
	tot = std::unique(que, que + tot) - que;
	seg_init(0, tot - 1);
	seg_upd(0, tot - 1, 0, (Info){0, INF});
	seg_upd(0, tot - 1, tot - 1, (Info){INF, 0});
	LL ans = INF;
	for(int i = 0; i < n; ++i)
	{
		int pL = std::lower_bound(que, que + tot, a[i].L) - que;
		int pM = std::lower_bound(que, que + tot, a[i].M) - que;
		int pR = std::upper_bound(que, que + tot, a[i].R) - que - 1;
		Info val = seg_que(0, tot - 1, pL, pR);
		upd(ans, val.first + val.second + a[i].C);
		val.first += a[i].C;
		val.second += a[i].C;
		seg_upd(0, tot - 1, pM, val);
	}
	printf("%lld\n", ans < INF ? ans : -1);
	return 0;
}
