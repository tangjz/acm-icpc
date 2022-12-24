#include <cstdio>
int n, k, num[41][41], f[41][7];
int main()
{
 	int i, j, tmp;
 	char ch;
	scanf("%d%d", &n, &k);
	for(i = 1; i <= n; ++i)
	{
		while((ch = getchar()) < '0' || ch > '9');
		num[i][i] = ch - '0';
	}
	for(i = 1; i <= n; ++i)
	{
		for(j = i + 1; j <= n; ++j) num[i][j] = (num[i][j - 1] << 3) + (num[i][j - 1] << 1) + num[j][j];
		f[i][0] = num[1][i];
	}
	for(j = 1; j <= k; ++j)
		for(i = j + 1; i <= n; ++i)
			for(tmp = j; tmp < i; ++tmp)
				if(f[i][j] < f[tmp][j - 1] * num[tmp + 1][i]) f[i][j] = f[tmp][j - 1] * num[tmp + 1][i];
	printf("%d\n", f[n][k]);
}