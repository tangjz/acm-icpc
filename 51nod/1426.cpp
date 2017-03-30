#include <stdio.h>
#include <cstring>
#include <algorithm>
const int maxn = 1000001;
int n, m;
struct Seg {
	int cL, cM, cR;
} seg[maxn << 1 | 1];
char str[maxn];
inline int seg_idx(int L, int R)
{
	return (L + R) | (L < R);
}
inline Seg seg_merge(Seg const &a, Seg const &b)
{
	int com = std::min(a.cL, b.cR);
	return (Seg){a.cL + b.cL - com, a.cM + b.cM + com, a.cR + b.cR - com};
}
void seg_init(int L, int R)
{
	int rt = seg_idx(L, R);
	if(L == R)
	{
		seg[rt] = (Seg){str[L - 1] == '(', 0, str[L - 1] == ')'};
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	seg_init(L, M);
	seg_init(M + 1, R);
	seg[rt] = seg_merge(seg[lch], seg[rch]);
}
Seg seg_que(int L, int R, int l, int r)
{
	int rt = seg_idx(L, R);
	if(l <= L && R <= r)
		return seg[rt];
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(r <= M)
		return seg_que(L, M, l, r);
	if(l > M)
		return seg_que(M + 1, R, l, r);
	return seg_merge(seg_que(L, M, l, r), seg_que(M + 1, R, l, r));
}
int main()
{
	scanf("%s%d", str, &m);
	n = strlen(str);
	seg_init(1, n);
	while(m--)
	{
		int L, R;
		scanf("%d%d", &L, &R);
		printf("%d\n", seg_que(1, n, L, R).cM << 1);
	}
	return 0;
}
