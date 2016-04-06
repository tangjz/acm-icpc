#include <cstdio>
#include <cstring>
const int maxn = 202;
int t, n, a[maxn], b[maxn], f[maxn][maxn];
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		memset(f, 0x3f, sizeof f);
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		for(int i = 1; i <= n; ++i)
			scanf("%d", b + i);
		for(int i = 1; i <= n; ++i)
			f[i][i] = a[i] + b[i - 1] + b[i + 1];
		for(int len = 2; len <= n; ++len)
			for(int i = 1; i <= n; ++i)
			{
				int j = i + len - 1;
				if(j > n)
					continue;
				for(int k = i; k <= j; ++k)
				{
					int tmp = a[k];
					if(i < k)
						tmp += f[i][k - 1];
					if(k < j)
						tmp += f[k + 1][j];
					if(f[i][j] > tmp)
						f[i][j] = tmp;
				}
				f[i][j] += b[i - 1] + b[j + 1];
			}
		printf("Case #%d: %d\n", Case, f[1][n]);
	}
	return 0;
}
