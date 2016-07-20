#include <cmath>
#include <cstdio>
const int maxn = 31, maxv = 201, maxs = 61;
const double eps = 1e-8, INF = 1e9;
int n, x[maxn], y[maxn], val[maxn], sum, f[maxn][maxn * maxv], dist;
char str[maxs];
inline int dcmp(double x)
{
	return (x > eps) - (x < -eps);
}
inline double dis(int a, int b)
{
	return sqrt((x[a] - x[b]) * (x[a] - x[b]) + (y[a] - y[b]) * (y[a] - y[b]));
}
int main()
{
	for(int Case = 1; scanf("%d", &n) == 1 && n; ++Case)
	{
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d%d%d", x + i, y + i, val + i);
			sum += val[i];
		}
		x[++n] = 0;
		y[n] = 0;
		val[n] = 0;
		f[0][0] = 0;
		for(int i = 1; i <= sum; ++i)
			f[0][i] = INF;
		for(int i = 1; i <= n; ++i)
			for(int j = 0; j <= sum; ++j)
			{
				f[i][j] = INF;
				for(int k = 0; k < i; ++k)
					if(val[k] <= j && f[i][j] > f[k][j - val[k]] + dis(k, i))
						f[i][j] = f[k][j - val[k]] + dis(k, i);
			}
		printf("Race %d\n", Case);
		while(scanf("%s%d", str, &dist) == 2 && !(str[0] == '#' && str[1] == '\0' && dist == 0))
		{
			int ans = 0;
			for(int i = sum; i >= 0; --i)
				if(dist >= f[n][i])
				{
					ans = i;
					break;
				}
			printf("%s: %d\n", str, ans);
		}
	}
	return 0;
}
