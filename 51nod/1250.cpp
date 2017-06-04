#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxn = 3001, mod = 1000000007;
int n, m, mx, f[2][maxn], g[2][maxn], cur, pre = 1;
inline void mod_inc(int &x, int y)
{
	(x += y) >= mod && (x -= mod);
}
inline void mod_dec(int &x, int y)
{
	(x -= y) < 0 && (x += mod);
}
int main()
{
	scanf("%d%d", &n, &m);
	mx = n < m ? m : n;
	f[cur][0] = g[cur][0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		pre ^= 1;
		cur ^= 1;
		for(int j = 0; j <= mx; ++j)
		{
			f[cur][j] = f[pre][j];
			g[cur][j] = (i - 1LL) * g[pre][j] % mod;
			if(j > 0)
			{
				mod_inc(f[cur][j], f[cur][j - 1]);
				mod_inc(g[cur][j], g[pre][j - 1]);
			}
			if(j >= i)
				mod_dec(f[cur][j], f[pre][j - i]);
		}
	}
	int sf = 0, sg = 0;
	for(int j = 0; j <= mx; ++j)
	{
		if(j <= m && (j & 1) == (m & 1))
			mod_inc(sf, f[cur][j]);
		if(j + m >= n)
			mod_inc(sg, g[cur][j]);
	}
	printf("%d %d\n", sf, sg);
	return 0;
}
