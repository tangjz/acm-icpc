#include <cstdio>
typedef long long LL;
const int maxn = 2001, maxm = 100001, maxv = 10000001, mod = 1000000007;
int tot, pr[maxv >> 3 | 1], d[maxv], f[maxv];
int n, m, typ, a[maxm], (*b)[maxn] = (int (*)[maxn])f, ans;
int p[maxn], dx, dy, c[maxn], st, tim[maxn], mx, cnt[maxm];
inline void mod_inc(int &x, int y, int p)
{
	(x += y) >= p && (x -= p);
}
int solve(int val)
{
	if(tim[val] == st)
		return c[val];
	tim[val] = st;
	c[val] = 0;
	if(val >= dx)
		mod_inc(c[val], solve(val - dx), mod);
	if(val >= dy)
		mod_inc(c[val], solve(val - dy), mod);
	if(val >= dx + dy)
	{
		mod_inc(c[val], mod - solve(val - dx - dy), mod);
		mod_inc(c[val], p[val - dx - dy], mod);
	}
	return c[val];
}
int main()
{
	scanf("%d%d%d", &typ, &n, &m);
	for(int i = 0; i < m; ++i)
		scanf("%d", a + i);
	if(typ == 1)
		for(int i = 1; i <= (n >> 1); ++i)
			for(int j = i; j <= n - i; ++j)
				b[i][j] = m > 1;
	else if(typ == 2)
	{
		for(int i = 1; i <= n; ++i)
			b[0][i] = i % m;
		for(int i = 1; i <= (n >> 1); ++i)
			for(int j = i; j <= n - i; ++j)
				b[i][j] = i < j - i ? b[i][j - i] : b[j - i][i];
	}
	else
		for(int i = 1; i <= n; ++i)
			for(int j = 1, v = i % m; j <= n - i; ++j, v = (LL)v * i % m)
			{
				if(i <= j)
				{
					mod_inc(b[i][j], v, m);
					b[i][j] = (b[i][j] + (i ^ j)) % m;
				}
				if(j <= i)
					mod_inc(b[j][i], v, m);
			}
	p[0] = 1;
	for(int i = 1; i <= n; ++i)
		for(int j = i; j <= n; ++j)
			mod_inc(p[j], p[j - i], mod);
	for(dx = 1; dx <= (n >> 1); ++dx)
	{
		int ctr = 0;
		for(int j = 1, k = n - (dx << 1); k >= 0; ++j, k -= dx)
			ctr = (ctr + (LL)j * p[k]) % mod;
		mod_inc(cnt[b[dx][dx]], ctr, mod);
		for(dy = dx + 1; dy <= n - dx; ++dy)
		{
			++st;
			mod_inc(cnt[b[dx][dy]], solve(n), mod);
		}
	}
	for(int i = 0; i < m; ++i)
		if(cnt[i] && mx < a[i])
			mx = a[i];
	f[1] = 1;
	for(int i = 2; i <= mx; ++i)
	{
		if(!d[i])
		{
			pr[tot++] = d[i] = i;
			f[i] = (i - 1) << 1;
			for(int cur = i, pre = 1, ctr = 2, lim = mx / i; pre <= lim; pre = cur, cur *= i, ++ctr)
			{
				d[cur] = cur;
				f[cur] = (LL)(cur - pre) * ctr % mod;
			}
		}
		for(int j = 0, k; (k = i * pr[j]) <= mx; ++j)
			if(d[i] % pr[j])
			{
				d[k] = pr[j];
				f[k] = (LL)f[i] * f[pr[j]] % mod;
			}
			else
			{
				if(!d[k])
				{
					d[k] = d[i] * pr[j];
					f[k] = (LL)f[k / d[k]] * f[d[k]] % mod;
				}
				break;
			}
	}
	for(int i = 0; i < m; ++i)
		if(cnt[i] && a[i])
			ans = (ans + (LL)f[a[i]] * cnt[i]) % mod;
	printf("%d\n", ans);
	return 0;
}
