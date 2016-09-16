#include <stdio.h>
const int maxn = 50001, maxd = 30;
int n, q, seg_tot, root[maxn];
struct Trie
{
	int cnt, ch[2];
} seg[maxn * maxd];
void update(int &rt, int dep, int x)
{
	int last = rt;
	seg[rt = ++seg_tot] = seg[last];
	++seg[rt].cnt;
	if(dep == -1)
		return;
	update(seg[rt].ch[(x >> dep) & 1], dep - 1, x);
}
int query(int rtL, int rtR, int dep, int x)
{
	if(dep == -1)
		return 0;
	int o = (x >> dep) & 1;
	if(seg[seg[rtL].ch[o ^ 1]].cnt < seg[seg[rtR].ch[o ^ 1]].cnt)
		return query(seg[rtL].ch[o ^ 1], seg[rtR].ch[o ^ 1], dep - 1, x) | 1 << dep;
	return query(seg[rtL].ch[o], seg[rtR].ch[o], dep - 1, x);
}
int main()
{
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; ++i)
	{
		int x;
		scanf("%d", &x);
		root[i] = root[i - 1];
		update(root[i], maxd - 1, x);
	}
	while(q--)
	{
		int l, r, x;
		scanf("%d%d%d", &x, &l, &r);
		printf("%d\n", query(root[l], root[r + 1], maxd - 1, x));
	}
	return 0;
}
