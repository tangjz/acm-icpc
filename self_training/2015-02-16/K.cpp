#include <cstdio>
#include <cstring>
const int maxn = 101, maxm = 101;
int n, m, w[maxm], f[maxm];
int main()
{
	while(scanf("%d%d", &n, &m) == 2 && n + m)
	{
		memset(f, 0, sizeof f);
		while(n--)
		{
			for(int i = 1; i <= m; ++i)
				scanf("%d", w + i);
			for(int i = m; i > 0; --i)
				for(int k = 1; k <= m && k <= i; ++k)
					if(f[i] < f[i - k] + w[k])
						f[i] = f[i - k] + w[k];
		}
		printf("%d\n", f[m]);
	}
	return 0;
}
