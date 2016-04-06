#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 105;
const double eps = 1e-8, delta = 2.9e4;
int n, a[maxn][2], b[maxn][2], match[maxn];
double g[maxn][maxn], lx[maxn], ly[maxn];
bool sx[maxn], sy[maxn];
int sgn(double x)
{
	return (x > eps) - (x < -eps);
}
int sqr(int x)
{
	return x * x;
}
bool path(int u)
{
	sx[u] = 1;
	for(int v = 0; v < n; ++v)
	{
		if(sy[v] || sgn(lx[u] + ly[v] - g[u][v]))
			continue;
		sy[v] = 1;
		if(match[v] == -1 || path(match[v]))
		{
			match[v] = u;
			return 1;
		}
	}
	return 0;
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		for(int i = 0; i < n; ++i)
			scanf("%d%d", b[i] + 0, b[i] + 1);
		for(int i = 0; i < n; ++i)
			scanf("%d%d", a[i] + 0, a[i] + 1);
		for(int i = 0; i < n; ++i)
		{
			lx[i] = ly[i] = 0;
			for(int j = 0; j < n; ++j)
			{
				g[i][j] = delta - sqrt(sqr(a[i][0] - b[j][0]) + sqr(a[i][1] - b[j][1]));
				if(lx[i] < g[i][j])
					lx[i] = g[i][j];
			}
		}
		memset(match, -1, sizeof match);
		for(int i = 0; i < n; ++i)
			while(1)
			{
				memset(sx, 0, sizeof sx);
				memset(sy, 0, sizeof sy);
				if(path(i))
					break;
				double dx = 1e10;
				for(int j = 0; j < n; ++j)
				{
					if(!sx[j])
						continue;
					for(int k = 0; k < n; ++k)
						if(!sy[k] && dx > lx[j] + ly[k] - g[j][k])
							dx = lx[j] + ly[k] - g[j][k];
				}
				for(int j = 0; j < n; ++j)
				{
					if(sx[j])
						lx[j] -= dx;
					if(sy[j])
						ly[j] += dx;
				}
			}
		for(int i = 0; i < n; ++i)
			printf("%d\n", match[i] + 1);
	}
	return 0;
}
