#include <cstdio>
#include <algorithm>
const int maxn = 101;
int r, c, n, m, bx[maxn], by[maxn], wx[maxn], wy[maxn], tot, que[maxn << 1], ans, delta;
int main()
{
	scanf("%d%d%d%d", &r, &c, &n, &m);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d%d", bx + i, by + i);
		if(bx[i] > r - 8 || by[i] > c - 4)
		{
			--i;
			--n;
			++delta;
		}
	}
	if(!n)
	{
		printf("%d\n", delta);
		return 0;
	}
	for(int i = 0; i < m; ++i)
		scanf("%d%d", wx + i, wy + i);
	tot = 0;
	for(int i = 0; i < n; ++i)
		que[tot++] = bx[i];
	for(int i = 0; i < m; ++i)
		que[tot++] = wx[i];
	std::sort(que, que + tot);
	r = tot = std::unique(que, que + tot) - que;
	for(int i = 0; i < n; ++i)
		bx[i] = std::lower_bound(que, que + tot, bx[i]) - que;
	for(int i = 0; i < m; ++i)
		wx[i] = std::lower_bound(que, que + tot, wx[i]) - que;
	ans = n + m;
	for(int L = 0; L < r; ++L)
		for(int R = L; R < r; ++R)
		{
			tot = 0;
			for(int i = 0; i < n; ++i)
				if(bx[i] >= L && bx[i] <= R)
					que[tot++] = by[i] << 1 | 0;
			for(int i = 0; i < m; ++i)
				if(wx[i] >= L && wx[i] <= R)
					que[tot++] = wy[i] << 1 | 1;
			std::sort(que, que + tot);
			int mx = 0, cb = 0, cw = 0;
			for(int i = 0, j = 0; i < tot; i = j)
			{
				for( ; j < tot && (que[i] >> 1) == (que[j] >> 1); ++j)
					que[j] & 1 ? ++cw : ++cb;
				if(ans > n + cw - cb - mx)
					ans = n + cw - cb - mx;
				if(mx < cw - cb)
					mx = cw - cb;
			}
		}
	printf("%d\n", ans + delta);
	return 0;
}
