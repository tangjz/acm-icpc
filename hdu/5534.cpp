#include <cstdio>
#include <cstring>
const int maxn = 2020, INF = 0x3f3f3f3f;
int t, n, f0, f[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		memset(f, 0x3f, sizeof f);
		f[0] = 0;
		scanf("%d%d", &n, &f0);
		for(int i = 1, fi; i <= n - 2; ++i)
		{
			scanf("%d", &fi);
			fi -= f0;
			for(int j = i; j <= n - 2; ++j)
				if(f[j] == INF || f[j] < f[j - i] + fi)
					f[j] = f[j - i] + fi;
		}
		printf("%d\n", f[n - 2] + n * f0);
	}
	return 0;
}
