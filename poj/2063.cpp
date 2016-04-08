#include <cstdio>
#include <cstring>
const int maxd = 11, maxv = 45260;
int t, n, m, v, c[maxd], w[maxd], f[maxv];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d", &v, &m, &n);
		for(int i = 0; i < n; ++i)
		{
			scanf("%d%d", c + i, w + i);
			c[i] /= 1000;
		}
		while(m--)
		{
			int vv = v / 1000;
			memset(f, 0, sizeof f);
			for(int i = 0; i < n; ++i)
				for(int j = c[i]; j <= vv; ++j)
					if(f[j] < f[j - c[i]] + w[i])
						f[j] = f[j - c[i]] + w[i];
			v += f[vv];
		}
		printf("%d\n", v);
	}
	return 0;
}