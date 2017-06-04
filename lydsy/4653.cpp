#include <stdio.h>
#include <algorithm>
const int maxn = 500001, INF = 0x3f3f3f3f;
int n, m, tot, que[maxn << 1 | 1], ans;
struct Node {
	int L, R; // [L, R)
	void parse() {
		scanf("%d%d", &L, &R);
		que[tot++] = L;
		que[tot++] = ++R;
	}
	int len() const {
		return R - L;
	}
	bool operator < (Node const &t) const {
		return len() < t.len();
	}
} a[maxn];
struct Seg {
	int val, tag;
} seg[maxn << 2 | 1];
inline int seg_idx(int L, int R)
{
	return (L + R) | (L < R);
}
void seg_upd(int L, int R, int qL, int qR, int v)
{
	int rt = seg_idx(L, R);
	if(qL <= L && R <= qR)
	{
		seg[rt].val += v;
		seg[rt].tag += v;
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(seg[rt].tag)
	{
		seg[lch].val += seg[rt].tag;
		seg[lch].tag += seg[rt].tag;
		seg[rch].val += seg[rt].tag;
		seg[rch].tag += seg[rt].tag;
		seg[rt].tag = 0;
	}
	if(qL <= M)
		seg_upd(L, M, qL, qR, v);
	if(M < qR)
		seg_upd(M + 1, R, qL, qR, v);
	seg[rt].val = std::max(seg[lch].val, seg[rch].val);
}
void upd(int &x, int y)
{
	x > y && (x = y);
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		a[i].parse();
	std::sort(a, a + n);
	std::sort(que, que + tot);
	tot = std::unique(que, que + tot) - que;
	ans = INF;
	for(int i = 0, j = 0; i < n; ++i)
	{
		for( ; j < n && seg[seg_idx(0, tot - 1)].val < m; ++j)
		{
			int pL = std::lower_bound(que, que + tot, a[j].L) - que;
			int pR = std::lower_bound(que, que + tot, a[j].R) - que;
			seg_upd(0, tot - 1, pL, pR - 1, 1);
		}
		if(seg[seg_idx(0, tot - 1)].val >= m)
			upd(ans, a[j - 1].len() - a[i].len());
		int pL = std::lower_bound(que, que + tot, a[i].L) - que;
		int pR = std::lower_bound(que, que + tot, a[i].R) - que;
		seg_upd(0, tot - 1, pL, pR - 1, -1);
	}
	printf("%d\n", ans == INF ? -1 : ans);
	return 0;
}
