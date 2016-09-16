#include <cstdio>
#include <cstring>
const int maxn = 6, maxm = 7777, maxs = 51;
int t, m, n, q, w[maxm];
long long f[maxn][maxs];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		memset(f, 0, sizeof f);
		scanf("%d%d%d", &m, &n, &q);
		for(int i = 0; i < m; ++i)
		{
			char str[maxs];
			scanf("%s", str);
			w[i] = strlen(str);
		}
		f[0][0] = 1;
		for(int i = 1; i <= n; ++i)
			for(int j = 0; j < m; ++j)
				for(int k = w[j]; k < maxs; ++k)
					f[i][k] += f[i - 1][k - w[j]];
		while(q--)
		{
			int l;
			scanf("%d", &l);
			printf("%I64d\n", f[n][l]);
		}
	}
	return 0;
}
