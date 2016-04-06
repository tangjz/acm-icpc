#include <cstdio>
#include <cstring>
const int maxn = 131072 << 1, mod = 61;
int n, m;
struct SegTree
{
	int sum[6], tag;
} seg[maxn];
int sqr(int x)
{
	return x * x % mod;
}
void push_up(int o)
{
	for(int i = 0, now1 = seg[o + o].tag, now2 = seg[o + o + 1].tag; i < 6; ++i)
	{
		seg[o].sum[i] = seg[o + o].sum[now1++] + seg[o + o + 1].sum[now2++];
		if(seg[o].sum[i] >= mod)
			seg[o].sum[i] -= mod;
		if(now1 >= 6)
			now1 = 2;
		if(now2 >= 6)
			now2 = 2;
	}
}
void push_down(int o)
{
	if(!seg[o].tag)
		return;
	seg[o + o].tag += seg[o].tag;
	if(seg[o + o].tag >= 6)
		seg[o + o].tag = (seg[o + o].tag - 2) % 4 + 2;
	seg[o + o + 1].tag += seg[o].tag;
	if(seg[o + o + 1].tag >= 6)
		seg[o + o + 1].tag = (seg[o + o + 1].tag - 2) % 4 + 2;
	seg[o].tag = 0;
}
void build(int o, int L, int R)
{
	if(L == R)
	{
		scanf("%d", &seg[o].sum[0]);
		seg[o].sum[0] %= mod;
		for(int i = 1; i < 6; ++i)
			seg[o].sum[i] = sqr(seg[o].sum[i - 1]);
		return;
	}
	int M = L + R >> 1;
	build(o + o, L, M);
	build(o + o + 1, M + 1, R);
	push_up(o);
}
void mul(int o, int L, int R, int l, int r)
{
	if(L == l && R == r)
	{
		++seg[o].tag;
		if(seg[o].tag >= 6)
			seg[o].tag = 2;
		return;
	}
	int M = L + R >> 1;
	push_down(o);
	if(r <= M)
		mul(o + o, L, M, l, r);
	else if(l > M)
		mul(o + o + 1, M + 1, R, l, r);
	else
	{
		mul(o + o, L, M, l, M);
		mul(o + o + 1, M + 1, R, M + 1, r);
	}
	push_up(o);
}
int query(int o, int L, int R, int l, int r)
{
	if(L == l && R == r)
		return seg[o].sum[seg[o].tag];
	int M = L + R >> 1, ret = 0;
	push_down(o);
	if(r <= M)
		ret = query(o + o, L, M, l, r);
	else if(l > M)
		ret = query(o + o + 1, M + 1, R, l, r);
	else
	{
		ret = query(o + o, L, M, l, M) + query(o + o + 1, M + 1, R, M + 1, r);
		if(ret >= mod)
			ret -= mod;
	}
	push_up(o);
	return ret;
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		memset(seg, 0, sizeof seg);
		build(1, 1, n);
		while(m--)
		{
			int l, r;
			char op[2];
			scanf("%s%d%d", op, &l, &r);
			if(op[0] == 'S')
				mul(1, 1, n, l, r);
			else
				printf("%d\n", sqr(query(1, 1, n, l, r)));
		}
	}
	return 0;
}
