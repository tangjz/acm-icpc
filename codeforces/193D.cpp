#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 300002;
int n, p[maxn], f[maxn];
long long ans;
struct SegTree
{
	int v, c1, c2, d;
} seg[maxn << 1];
inline int idx(int L, int R)
{
	return L + R | L != R;
}
void push_up(int L, int R)
{
	int M = L + R >> 1, o = idx(L, R), lch = idx(L, M), rch = idx(M + 1, R);
	seg[o].v = min(seg[lch].v + seg[lch].d, seg[rch].v + seg[rch].d);
	seg[o].c1 = seg[o].c2 = 0;
	if(seg[o].v == seg[lch].v + seg[lch].d)
	{
		seg[o].c1 += seg[lch].c1;
		seg[o].c2 += seg[lch].c2;
	}
	else if(seg[o].v + 1 == seg[lch].v + seg[lch].d)
		seg[o].c2 += seg[lch].c1;
	if(seg[o].v == seg[rch].v + seg[rch].d)
	{
		seg[o].c1 += seg[rch].c1;
		seg[o].c2 += seg[rch].c2;
	}
	else if(seg[o].v + 1 == seg[rch].v + seg[rch].d)
		seg[o].c2 += seg[rch].c1;
}
void push_down(int L, int R)
{
	int o = idx(L, R);
	if(!seg[o].d)
		return;
	int M = L + R >> 1, lch = idx(L, M), rch = idx(M + 1, R);
	seg[o].v += seg[o].d;
	seg[lch].d += seg[o].d;
	seg[rch].d += seg[o].d;
	seg[o].d = 0;
}
void init(int L, int R)
{
	seg[idx(L, R)].c1 = R - L + 1;
	if(L == R)
		return;
	int M = L + R >> 1;
	init(L, M);
	init(M + 1, R);
}
void upd(int L, int R, int l, int r, int x)
{
	if(l <= L && R <= r)
	{
		seg[idx(L, R)].d += x;
		return;
	}
	int M = L + R >> 1;
	push_down(L, R);
	if(l <= M)
		upd(L, M, l, r, x);
	if(r > M)
		upd(M + 1, R, l, r, x);
	push_up(L, R);
}
int que(int L, int R, int l, int r)
{
	if(l <= L && R <= r)
	{
		int o = idx(L, R);
		if(seg[o].v + seg[o].d == 1)
			return seg[o].c1 + seg[o].c2;
		if(seg[o].v + seg[o].d == 2)
			return seg[o].c1;
		return 0;
	}
	int M = L + R >> 1, ret = 0;
	push_down(L, R);
	if(l <= M)
		ret += que(L, M, l, r);
	if(r > M)
		ret += que(M + 1, R, l, r);
	push_up(L, R);
	return ret;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1, x; i <= n; ++i)
	{
		scanf("%d", &x);
		p[x] = i;
	}
	init(1, n);
	for(int i = 1; i <= n; ++i)
	{
		int x = f[p[i] - 1], y = f[p[i] + 1];
		if(x > y)
			swap(x, y);
		if(y < i)
			upd(1, n, y + 1, i, 1);
		if(x >= 1)
			upd(1, n, 1, x, -1);
		f[p[i]] = i;
		ans += que(1, n, 1, i);
	}
	printf("%I64d\n", ans - n);
	return 0;
}
