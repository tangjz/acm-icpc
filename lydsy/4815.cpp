#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 4000001, maxm = 2001, mod = 1000000007;
int t, n, sqn, f[maxn], a[maxn], b[maxn], id[maxn], dt[maxm];
inline void mod_inc(int &x, int y)
{
	(x += y) >= mod && (x -= mod);
}
int main()
{
	scanf("%d%d", &t, &n);
	int &tot = sqn, *pr = id, *d = b;
	f[1] = a[1] = 1;
	for(int i = 2; i <= n; ++i)
	{
		if(!d[i])
		{
			f[i] = i - 1;
			pr[tot++] = d[i] = i;
		}
		for(int j = 0, k; (k = i * pr[j]) <= n; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
			{
				f[k] = f[i] * pr[j];
				break;
			}
			else
				f[k] = f[i] * (pr[j] - 1);
		}
		a[i] = (LL)i * i % mod; 
		f[i] = (f[i - 1] + (LL)a[i] * f[i]) % mod;
	}
	for(sqn = 1; sqn * sqn < n; ++sqn);
	for(int i = 1, j = 0, r = 0; i <= n; ++i, ((++r == sqn) && (++j, r = 0)))
	{
		mod_inc(b[i] = a[i], b[i - 1]);
		id[i] = j;
	}
	while(t--)
	{
		int x, y, m;
		LL val;
		scanf("%d%d%lld%d", &x, &y, &val, &m);
		int r = std::__gcd(x, y), v = val / (x / r) / (y / r) % mod;
		if(a[r] != v)
		{
			int diff = v - a[r];
			if(diff < 0)
				diff += mod;
			for(int i = r, j = std::min((id[r] + 1) * sqn, n); i <= j; ++i)
				mod_inc(b[i], diff);
			for(int i = id[r] + 1, j = id[n]; i <= j; ++i)
				mod_inc(dt[i], diff);
			a[r] = v;
		}
		int last = 0, cur, ans = 0;
		for(int i = 1, j, k; i <= m; i = j + 1)
		{
			k = m / i;
			j = m / k;
			mod_inc(cur = b[j], dt[id[j]]);
			if(last == cur)
				continue;
			ans = (ans + (LL)(cur - last) * f[k]) % mod;
			last = cur;
		}
		if(ans < 0)
			ans += mod;
		printf("%d\n", ans);
	}
	return 0;
}
