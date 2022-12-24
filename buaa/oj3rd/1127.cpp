#include <cstdio>
int n, k;
long long a[101][101];
int main()
{
	a[0][0] = 1;
	for(int i = 1; i <= 100; ++i)
	{
		a[i][0] = 1;
		for(int j = 1; j <= i; ++j)
			a[i][j] = a[i - 1][j] + a[i - 1][j - 1];
	}
	while(scanf("%d%d", &n, &k) == 2)
	{
		while(k--)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			if(x >= y && x <= n && y > 0)
				printf("%lld\n", a[x - 1][y - 1]);
			else
				puts("-1");
		}
	}
	return 0;
}

