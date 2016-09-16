#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 100001, maxd = 18, maxs = 26;
int n, tot, lim[maxn], seq[maxn], tim, pos[maxn], root[maxn], mx;
struct Trie
{
	int ch[maxs];
} e[maxn];
struct Segment
{
	int val, lch, rch;
} seg[maxn * maxd];
void insert(int idx)
{
	int rt = 0, i;
	static char str[maxn];
	scanf("%s", str);
	for(i = 0; str[i]; ++i)
	{
		str[i] -= 'a';
		if(!e[rt].ch[(int)str[i]])
		{
			pos[tot] = 0;
			e[rt].ch[(int)str[i]] = tot;
			memset(e + (tot++), 0, sizeof e[0]);
		}
		rt = e[rt].ch[(int)str[i]];
		seq[++tim] = pos[rt];
		if(mx < pos[rt])
			mx = pos[rt];
		pos[rt] = tim;
	}
	lim[idx] = lim[idx - 1] + i;
}
void update(int &rt, int L, int R, int x)
{
	int last = rt;
	seg[rt = ++tot] = seg[last];
	++seg[rt].val;
	if(L == R)
		return;
	int M = L + R >> 1;
	if(x <= M)
		update(seg[rt].lch, L, M, x);
	else
		update(seg[rt].rch, M + 1, R, x);
}
int query(int rt, int L, int R, int x)
{
	if(R <= x)
		return seg[rt].val;
	int M = L + R >> 1;
	if(x <= M)
		return query(seg[rt].lch, L, M, x);
	return seg[seg[rt].lch].val + query(seg[rt].rch, M + 1, R, x);
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		tot = tim = mx = 0;
		memset(e + (tot++), 0, sizeof e[0]);
		for(int i = 1; i <= n; ++i)
			insert(i);
		tot = 0;
		for(int i = 1, j = 1; i <= n; ++i)
			for(root[i] = root[i - 1]; j <= lim[i]; ++j)
				update(root[i], 0, mx, seq[j]);
		int m, l, r, z = 0;
		scanf("%d", &m);
		while(m--)
		{
			scanf("%d%d", &l, &r);
			l = (l + z) % n + 1;
			r = (r + z) % n + 1;
			if(l > r)
				std::swap(l, r);
			z = query(root[r], 0, mx, lim[l - 1]) - query(root[l - 1], 0, mx, lim[l - 1]);
			printf("%d\n", z);
		}
	}
	return 0;
}
