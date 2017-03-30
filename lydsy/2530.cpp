#include <stdio.h>
const int maxn = 3001;
int n, m;
bool e[maxn][maxn], ban[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	while(m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u][v] = e[v][u] = 1;
	}
	for(int i = 1; i <= n; ++i)
	{
		if(ban[i])
			continue;
		for(int j = i + 1; j <= n; ++j)
			if(!ban[j] && !e[i][j])
			{
				ban[i] = ban[j] = 1;
				break;
			}
	}
	bool fir = 1;
	for(int i = 1; i <= n; ++i)
	{
		if(ban[i])
			continue;
		if(!fir)
			putchar(' ');
		else
			fir = 0;
		printf("%d", i);
	}
	putchar('\n');
	return 0;
}
