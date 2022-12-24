#include <cstdio>
int n, m;
long long f[30][30];
bool g[30][30];
int main()
{
	int i, j;
	scanf("%d%d%d%d", &n, &m, &i ,&j);
	++i, ++j, ++n, ++m;
	f[1][1] = 1;
	g[i][j] = true;
	if(i - 1 > 0 && j - 2 > 0) g[i - 1][j - 2] = true;
	if(i - 2 > 0 && j - 1 > 0) g[i - 2][j - 1] = true;
	if(i - 1 > 0 && j + 2 <= m) g[i - 1][j + 2] = true;
	if(i - 2 > 0 && j + 1 <= m) g[i - 2][j + 1] = true;
	if(i + 1 <= n && j - 2 > 0) g[i + 1][j - 2] = true;
	if(i + 2 <= n && j - 1 > 0) g[i + 2][j - 1] = true;
	if(i + 1 <= n && j + 2 <= m) g[i + 1][j + 2] = true;
	if(i + 2 <= n && j + 1 <= m) g[i + 2][j + 1] = true;
	for(i = 1; i <= n; ++i)
		for(j = 1; j <= m; ++j) if((i!= 1 || j != 1) && !g[i][j]) f[i][j] = f[i - 1][j] + f[i][j - 1];
	printf("%I64d\n", f[n][m]);
}