#include <stdio.h>
#include <algorithm>
const int maxn = 20000;
int t, n, m, d[maxn], b[maxn], f[maxn], g[maxn], ans;
struct Segment
{
	int a, l, r;
	bool operator < (const Segment &t) const
	{
		return r < t.r;
	}
} s[maxn];
inline void upd(int &x, int y)
{
	if(x > y)
		x = y;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		for(register int i = 1; i < n; ++i)
		{
			scanf("%d", d + i);
			d[i] += d[i - 1];
		}
		for(register int i = 0, r; i < n; ++i)
		{
			scanf("%d%d%d", &s[i].a, &r, b + i);
			s[i].l = std::lower_bound(d, d + i + 1, d[i] - r) - d;
			s[i].r = std::upper_bound(d + i, d + n, d[i] + r) - d - 1;
			f[i] = (i > 0 ? f[i - 1] : 0) + b[i];
		}
		std::sort(s, s + n);
		ans = f[n - 1];
		for(register int i = 0; i < m; ++i)
		{
			g[n - 1] = f[n - 1];
			for(register int j = n - 2; j >= 0; --j)
			{
				g[j] = g[j + 1];
				upd(g[j], f[j]);
			}
			for(register int j = 0, k = 0; j < n; ++j)
			{
				if(j > 0)
					upd(f[j], f[j - 1] + b[j]);
				for( ; k < n && s[k].r == j; ++k)
					upd(f[j], (s[k].l > 0 ? g[s[k].l - 1] : 0) + s[k].a);
			}
			upd(ans, f[n - 1]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
