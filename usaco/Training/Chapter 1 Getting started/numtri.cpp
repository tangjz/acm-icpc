/*
ID: tangjin2
LANG: C++
TASK: numtri
*/
#include <cstdio>
int n, f[1001][1001];
int main()
{
	freopen("numtri.in", "r", stdin);
	freopen("numtri.out", "w", stdout);
	int i, j;
	scanf("%d", &n);
	for(i = 1; i <= n; ++i)
		for(j = 1; j <= i; ++j) scanf("%d", &f[i][j]);
	for(i = 1; i <= n; ++i)
		for(j = 1; j <= i; ++j) f[i][j] += f[i - 1][j - 1] > f[i - 1][j] ? f[i - 1][j - 1] : f[i - 1][j];
	for(i = 2; i <= n; ++i) if(f[n][i] > f[n][1]) f[n][1] = f[n][i];
	printf("%d\n", f[n][1]);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
