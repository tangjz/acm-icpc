#include <cstdio>
const int maxn = 262144;
int n, seg[maxn << 1], pos[maxn], val[maxn], ans[maxn];
void build(int o, int l, int r)
{
	if(l == r)
	{
		seg[o] = 1;
		return;
	}
	int m = l + r >> 1;
	build(o + o, l, m);
	build(o + o + 1, m + 1, r);
	seg[o] = seg[o + o] + seg[o + o + 1];
}
int query(int o, int l, int r, int v)
{
	if(l == r)
	{
		seg[o] = 0;
		return l;
	}
	int m = l + r >> 1, ret;
	if(v <= seg[o + o])
		ret = query(o + o, l, m, v);
	else
		ret = query(o + o + 1, m + 1, r, v - seg[o + o]);
	seg[o] = seg[o + o] + seg[o + o + 1];
	return ret;
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		for(int i = 1; i <= n; ++i)
			scanf("%d%d", pos + i, val + i);
		build(1, 1, n);
		for(int i = n; i >= 1; --i)
			ans[query(1, 1, n, pos[i] + 1)] = val[i];
		for(int i = 1; i <= n; ++i)
			printf("%d%c", ans[i], " \n"[i == n]);
	}
	return 0;
}
