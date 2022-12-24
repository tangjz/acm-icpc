#include <cstdio>
int n, k, f[201][7] = {};
int main()
{
	int i, j;
	scanf("%d%d", &n, &k);
	f[0][0] = 1;
	for(i = 1; i <= n; ++i)
		for(j = 1; j <= k; ++j)
			if(i >= j) f[i][j] = f[i - j][j] + f[i - 1][j - 1];
	printf("%d\n", f[n][k]);
	return 0;
}