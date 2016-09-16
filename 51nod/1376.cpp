#include <stdio.h>
#include <algorithm>
const int maxn = 50002, mod = 1000000007;
int n, a[maxn], tot, que[maxn];
struct Fenwick
{
	int val, cnt;
} bit[maxn];
void update(int x, int v, int c)
{
	for( ; x <= tot; x += x & -x)
		if(bit[x].val < v)
		{
			bit[x].val = v;
			bit[x].cnt = c;
		}
		else if(bit[x].val == v && (bit[x].cnt += c) >= mod)
			bit[x].cnt -= mod;
}
void query(int x, int &v, int &c)
{
	for(v = -1, c = 0; x > 0; x -= x & -x)
		if(v < bit[x].val)
		{
			v = bit[x].val;
			c = bit[x].cnt;
		}
		else if(v == bit[x].val && (c += bit[x].cnt) >= mod)
			c -= mod;
}
int main()
{
	scanf("%d", &n);
	que[tot++] = -1;
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		que[tot++] = a[i];
	}
	std::sort(que, que + tot);
	tot = std::unique(que, que + tot) - que;
	update(1, 0, 1);
	for(int i = 1; i <= n; ++i)
	{
		int k, s;
		a[i] = std::lower_bound(que, que + tot, a[i]) - que + 1;
		query(a[i] - 1, k, s);
		update(a[i], k + 1, s);
	}
	int k, s;
	query(tot, k, s);
	printf("%d\n", s);
	return 0;
}
