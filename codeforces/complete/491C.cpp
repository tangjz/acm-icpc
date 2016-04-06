#include <cstdio>
#include <cstring>
int n, m, g[55][55], lx[55], ly[55], match[55], sum;
char str1[2333333], str2[2333333], ans[55];
bool sx[55], sy[55];
bool path(int u)
{
	sx[u] = 1;
	for(int v = 1; v <= n; ++v)
		if(!sy[v] && lx[u] + ly[v] == g[u][v])
		{
			sy[v] = 1;
			if(!match[v] || path(match[v]))
			{
				match[v] = u;
				return 1;
			}
		}
	return 0;
}
int tran1(char ch)
{
	return ch >= 'a' && ch <= 'z' ? ch - 'a' + 1 : ch - 'A' + 27;
}
char tran2(int ch)
{
	return ch <= 26 ? ch + 'a' - 1 : ch + 'A' - 27;
}
int main()
{
	scanf("%d%d%s%s", &m, &n, str1, str2);
	for(int i = 0; i < m; ++i)
		++g[tran1(str1[i])][tran1(str2[i])];
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			if(lx[i] < g[i][j])
				lx[i] = g[i][j];
	memset(match, 0, sizeof(match));
	for(int u = 1; u <= n; ++u)
		while(1)
		{
			memset(sx, 0, sizeof(sx));
			memset(sy, 0, sizeof(sy));
			if(path(u))
				break;
			int dx = 0x7fffffff;
			for(int i = 1; i <= n; ++i)
				if(sx[i])
					for(int j = 1; j <= n; ++j)
						if(!sy[j] && dx > lx[i] + ly[j] - g[i][j])
							dx = lx[i] + ly[j] - g[i][j];
			for(int i = 1; i <= n; ++i)
			{
				if(sx[i])
					lx[i] -= dx;
				if(sy[i])
					ly[i] += dx;
			}
		}
	for(int i = 1; i <= n; ++i)
	{
		sum += g[match[i]][i];
		ans[match[i] - 1] = tran2(i);
	}
	ans[n] = '\0';
	printf("%d\n%s\n", sum, ans);
	return 0;
}
