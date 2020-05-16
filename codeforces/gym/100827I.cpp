#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1000001;
int t, n, q, tot, lnk[maxn], in[maxn], out[maxn];
struct Edge
{
	int nxt, v;
} e[maxn << 1];
struct Segment
{
	int maxv, minv, tag;
} seg[maxn << 1];
void dfs(int u)
{
	in[u] = ++tot;
	for(int it = lnk[u]; it != -1; it = e[it].nxt)
		dfs(e[it].v);
	out[u] = tot;
}
inline int seg_idx(int L, int R)
{
	return (L + R) | (L < R);
}
inline void push_up(Segment &rt, Segment lch, Segment rch)
{
	rt.maxv = max(lch.maxv, rch.maxv);
	rt.minv = min(lch.minv, rch.minv);
}
inline void push_down(Segment &rt, Segment &lch, Segment &rch)
{
	if(rt.tag)
	{
		lch.maxv += rt.tag;
		lch.minv += rt.tag;
		lch.tag += rt.tag;
		rch.maxv += rt.tag;
		rch.minv += rt.tag;
		rch.tag += rt.tag;
		rt.tag = 0;
	}
}
void build(int L, int R)
{

	int rt = seg_idx(L, R);
	seg[rt].tag = 0;
	if(L == R)
		return;
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	build(L, M);
	build(M + 1, R);
	push_up(seg[rt], seg[lch], seg[rch]);
}
void update(int L, int R, int l, int r, int v)
{
	int rt = seg_idx(L, R);
	if(l <= L && R <= r)
	{
		seg[rt].maxv += v;
		seg[rt].minv += v;
		seg[rt].tag += v;
		return;
	}
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	push_down(seg[rt], seg[lch], seg[rch]);
	if(l <= M)
		update(L, M, l, r, v);
	if(r > M)
		update(M + 1, R, l, r, v);
	push_up(seg[rt], seg[lch], seg[rch]);
}
Segment query(int L, int R, int l, int r)
{
	int rt = seg_idx(L, R);
	if(l <= L && R <= r)
		return seg[rt];
	int M = (L + R) >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	Segment ret;
	push_down(seg[rt], seg[lch], seg[rch]);
	if(r <= M)
		ret = query(L, M, l, r);
	else if(l > M)
		ret = query(M + 1, R, l, r);
	else
		push_up(ret, query(L, M, l, r), query(M + 1, R, l, r));
	push_up(seg[rt], seg[lch], seg[rch]);
	return ret;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		tot = 0;
		memset(lnk + 1, -1, n * sizeof(int));
		for(int i = 2; i <= n; ++i)
		{
			int fa;
			scanf("%d", &fa);
			e[tot] = (Edge){lnk[fa], i};
			lnk[fa] = tot++;
		}
		tot = 0;
		dfs(1);
		for(int i = 1; i <= n; ++i)
		{
			int val;
			scanf("%d", &val);
			seg[seg_idx(in[i], in[i])].maxv = seg[seg_idx(in[i], in[i])].minv = val;
		}
		build(1, n);
		scanf("%d", &q);
		while(q--)
		{
			char op[2];
			int x, v;
			scanf("%s", op);
			if(op[0] == 'R')
			{
				scanf("%d%d", &x, &v);
				update(1, n, in[x], out[x], v);
			}
			else
			{
				scanf("%d", &x);
				Segment ret = query(1, n, in[x], out[x]);
				printf("%d\n", ret.maxv - ret.minv);
			}
		}
	}

	return 0;
}
