#include <cstdio>
#include <cstring>
const int maxn = 11, maxs = 100, maxw = 1 << 11, mod = 1000000007;
int n, m, s, p[maxn], c[maxn], fa[maxn], e[maxn], ans;
int lim, size;
long long f[maxw][maxs + 1];
int main()
{
	while(scanf("%d%d%d", &n, &m, &s) == 3)
	{
		lim = 0;
		size = 1 << n;
		memset(fa, 0, sizeof fa);
		memset(e, 0, sizeof e);
		for(int i = 1, u, v; i < n; ++i)
		{
			scanf("%d%d", &u, &v);
			fa[--v] = --u;
		}
		for(int i = 1; i < n; ++i)
			for(int j = i; j; j = fa[j])
				e[fa[j]] |= 1 << i;
		for(int i = 0; i < n; ++i)
		{
			scanf("%d%d", p + i, c + i);
			if(c[i] < m - c[i])
				c[i] = m - c[i];
			if(lim < c[i])
				lim = c[i];
		}
		ans = 0;
		memset(f, 0, sizeof f);
		f[0][0] = 1;
		for(int i = 0; i <= lim; ++i)
		{
			for(int u = 0; u < n; ++u)
				if(i <= c[u])
					for(int j = 0; j < size; ++j)
						if(~(j >> u) & 1)
						{
							int jj = j ^ (1 << u), delta = __builtin_popcount(e[u] & j) * p[u];
							for(int k = delta; k <= s; ++k)
							{
								f[jj][k] += f[j][k - delta];
								if(i >= 1 && i <= m - c[u])
									f[jj][k] += f[j][k - delta];
							}
						}
			for(int j = 0; j < size; ++j)
				for(int k = 0; k <= s; ++k)
					f[j][k] %= mod;
		}
		printf("%d\n", f[size - 1][s]);
	}
	return 0;
}
