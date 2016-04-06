#include <cstdio>
const int maxv = 1e5 + 1;
int n, v, f[maxv], g[maxv];
int main()
{
	scanf("%d%d", &n, &v);
	while(n--)
	{
		int m, vv, c, w;
		scanf("%d%d", &vv, &m);
		for(int i = vv; i <= v; ++i)
			g[i] = f[i - vv];
		while(m--)
		{
			scanf("%d%d", &c, &w);
			for(int i = v; i >= c + vv; --i)
				if(g[i] < g[i - c] + w)
					g[i] = g[i - c] + w;
		}
		for(int i = vv; i <= v; ++i)
			if(f[i] < g[i])
				f[i] = g[i];
	}
	printf("%d\n", f[v]);
	return 0;
}
