#include <cstdio>
#include <cstring>
const int maxn = 2002, mod = 10;
int n, m, w[maxn];
char f[maxn], g[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	f[0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", w + i);
		for(int j = m; j >= w[i]; --j)
		{
			f[j] += f[j - w[i]];
			if(f[j] >= mod)
				f[j] -= mod;
		}
	}
	for(int i = 1; i <= n; ++i)
	{
		memcpy(g, f, sizeof f);
		for(int j = w[i]; j <= m; ++j)
		{
			if(g[j] < g[j - w[i]])
				g[j] += mod;
			g[j] -= g[j - w[i]];
		}
		for(int j = 1; j <= m; ++j)
			g[j] += '0';
		puts(g + 1);
	}
	return 0;
}
