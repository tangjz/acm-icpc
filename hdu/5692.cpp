#pragma comment(linker, "/STACK:10240000,10240000")
#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;
const long long INF = 0x3f3f3f3f3f3f3f3fLL;
int t, n, m, a[maxn], tot, seq[maxn], in[maxn], out[maxn];
vector<int> e[maxn];
struct Segment
{
	long long val, tag;	
} seg[maxn << 1];
void dfs(int u, int fa)
{
	seq[tot] = u;
	in[u] = tot++;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		if((*it) != fa)
			dfs(*it, u);
	out[u] = tot - 1;
}
inline int seg_idx(int L, int R)
{
	return L + R | L != R;
}
inline void merge(int o, int lch, int rch)
{
	seg[o].val = max(seg[lch].val, seg[rch].val);
}
inline void split(int o, int lch, int rch)
{
	if(seg[o].tag)
	{
		seg[lch].val += seg[o].tag;
		seg[lch].tag += seg[o].tag;
		seg[rch].val += seg[o].tag;
		seg[rch].tag += seg[o].tag;
		seg[o].tag = 0;
	}
}
void update(int L, int R, int l, int r, int v)
{
	int o = seg_idx(L, R);
	if(l <= L && R <= r)
	{
		seg[o].val += v;
		seg[o].tag += v;
		return;
	}
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	split(o, lch, rch);
	if(l <= M)
		update(L, M, l, r, v);
	if(r > M)
		update(M + 1, R, l, r, v);
	merge(o, lch, rch);
}
long long query(int L, int R, int l, int r)
{
	int o = seg_idx(L, R);
	if(l <= L && R <= r)
		return seg[o].val;
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	long long ret = -INF;
	split(o, lch, rch);
	if(l <= M)
		ret = max(ret, query(L, M, l, r));
	if(r > M)
		ret = max(ret, query(M + 1, R, l, r));
	merge(o, lch, rch);
	return ret;
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
			vector<int>().swap(e[i]);
		for(int i = 1; i < n; ++i)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
		}
		tot = 0;
		dfs(0, -1);
		memset(seg, 0, (tot << 1) * sizeof(Segment));
		for(int i = 0; i < n; ++i)
		{
			scanf("%d", a + i);
			update(0, tot - 1, in[i], out[i], a[i]);
		}
		printf("Case #%d:\n", Case);
		while(m--)
		{
			int typ, x, y;
			scanf("%d%d", &typ, &x);
			if(!typ)
			{
				scanf("%d", &y);
				update(0, tot - 1, in[x], out[x], y - a[x]);
				a[x] = y;
			}
			else
				printf("%I64d\n", query(0, tot - 1, in[x], out[x]));
		}
	}
	return 0;
}
