#include <cstdio>
#include <cstring>
const int maxn = 501, maxk = 7;
int t, n, k1, k2, k3, a, b, c;
double p[maxk * 3], f[maxn], g[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		memset(p, 0, sizeof p);
		scanf("%d%d%d%d%d%d%d", &n, &k1, &k2, &k3, &a, &b, &c);
		p[0] = 1.0 / (k1 * k2 * k3);
		for(int i = 1; i <= k1; ++i)
			for(int j = 1; j <= k2; ++j)
				for(int k = 1; k <= k3; ++k)
					if(i != a || j != b || k != c)
						p[i + j + k] += p[0];
		for(int i = n; i >= 0; --i)
		{
			f[i] = p[0];
			g[i] = 1;
			for(int j = 3; j <= k1 + k2 + k3 && i + j <= n; ++j)
			{
				f[i] += f[i + j] * p[j];
				g[i] += g[i + j] * p[j];
			}
		}
		printf("%.9f\n", g[0] / (1 - f[0]));
	}
	return 0;
}
