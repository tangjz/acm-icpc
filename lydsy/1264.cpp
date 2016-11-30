#include <stdio.h>
#include <algorithm>
const int maxn = 200000, maxd = 5;
int n, pos[maxn + 1][maxd + 1], mx, f[maxn * maxd + 1];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n * maxd; ++i)
	{
		int x;
		scanf("%d", &x);
		pos[x][++pos[x][0]] = i;
	}
	for(int i = 1; i <= n * maxd; ++i)
	{
		int x;
		scanf("%d", &x);
		for(int j = maxd; j > 0; --j)
		{
			int k = std::lower_bound(f, f + mx + 1, pos[x][j]) - f;
			f[k] = pos[x][j];
			if(mx < k)
				mx = k;
		}
	}
	printf("%d\n", mx);
	return 0;
}
