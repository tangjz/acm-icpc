#include <cstdio>
#include <cstring>
const int maxn = 110, maxm = 110, maxv2 = 101 * 101;
int n, m, a[maxm], b[maxm], f[maxv2];
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		for(int i = 1; i <= m; ++i)
			scanf("%d%d", a + i, b + i);
/*		memset(f, 0, sizeof f);
		for(int i = 1; i <= m; ++i)
			for(int j = b[i]; j < maxv2; ++j)
				if(f[j] < f[j - b[i]] + a[i])
					f[j] = f[j - b[i]] + a[i];
		for(int i = 0; i < maxv2; ++i)
			if(f[i] >= n)
			{
				printf("%d\n", i);
				break;
			}
*/
		int ans = 0x3f3f3f3f;
		for(int i = 1; i <= m; ++i)
			if(ans > ((n - 1) / a[i] + 1) * b[i])
				ans = ((n - 1) / a[i] + 1) * b[i];
		printf("%d\n", ans);
	}
	return 0;
}
