#include <stdio.h>
#include <algorithm>
const int maxn = 50001, maxd = 17;
int n, q, a[maxn], tot, que[maxn], seg_tot, root[maxn];
struct Segment
{
	int cnt, lch, rch;
} seg[maxn * maxd];
void update(int &rt, int L, int R, int x)
{
	int last = rt;
	seg[rt = ++seg_tot] = seg[last];
	++seg[rt].cnt;
	if(L == R)
		return;
	int M = L + R >> 1;
	if(x <= M)
		update(seg[rt].lch, L, M, x);
	else
		update(seg[rt].rch, M + 1, R, x);
}
int query(int rtL, int rtR, int L, int R, int cnt)
{
	while(L < R)
	{
		int M = L + R >> 1, val = seg[seg[rtR].rch].cnt - seg[seg[rtL].rch].cnt;
		if(val < cnt)
		{
			rtL = seg[rtL].lch;
			rtR = seg[rtR].lch;
			R = M;
			cnt -= val;
		}
		else
		{
			rtL = seg[rtL].rch;
			rtR = seg[rtR].rch;
			L = M + 1;
		}
	}
	return L;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		que[tot++] = a[i];
	}
	std::sort(que, que + tot);
	tot = std::unique(que, que + tot) - que;
	for(int i = 1; i <= n; ++i)
	{
		root[i] = root[i - 1];
		update(root[i], 0, tot - 1, std::lower_bound(que, que + tot, a[i]) - que);
	}
	scanf("%d", &q);
	while(q--)
	{
		int l, r, k;
		scanf("%d%d%d", &l, &r, &k);
		printf("%d\n", que[query(root[l], root[r + 1], 0, tot - 1, k)]);
	}
	return 0;
}
