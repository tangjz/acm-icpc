#include <cmath>
#include <cstdio>
const double INF = 1e9;
int a, b, n;
double mat[11][11], x, f[11][11][11][11][11];
template<class T>inline void update(T& x, const T& y) { if(x > y) x = y;}
double dfs(int x1, int y1, int x2, int y2, int k)
{
	double &ret = f[x1][y1][x2][y2][k];
	if(ret < INF) return ret;
	if(!k)
	{
		ret = mat[x2][y2] - mat[x1 - 1][y2] - mat[x2][y1 - 1] + mat[x1 - 1][y1 - 1] - x;
		return ret = ret * ret;
	}
	for(int i = 0; i < k; ++i)
	{
		for(int j = x1; j < x2; ++j)
			update(ret, dfs(x1, y1, j, y2, i) + dfs(j + 1, y1, x2, y2, k - i - 1));
		for(int j = y1; j < y2; ++j)
			update(ret, dfs(x1, y1, x2, j, i) + dfs(x1, j + 1, x2, y2, k - i - 1));
	}
	return ret;
}
int main()
{
	scanf("%d%d%d", &a, &b, &n);
	for(int i = 1; i <= a; ++i)
		for(int j = 1; j <= b; ++j)
		{
			scanf("%lf", &mat[i][j]);
			mat[i][j] += mat[i - 1][j] + mat[i][j - 1] - mat[i - 1][j - 1];
		}
	x = mat[a][b] / n;
	for(int x1 = 0; x1 <= a; ++x1)
		for(int y1 = 0; y1 <= b; ++y1)
			for(int x2 = 0; x2 <= a; ++x2)
				for(int y2 = 0; y2 <= b; ++y2)
					for(int w = 0; w < n; ++w)
						f[x1][y1][x2][y2][w] = INF;
	dfs(1, 1, a, b, n - 1);
	printf("%.2lf\n", sqrt(f[1][1][a][b][n - 1] / n));
	return 0;
}

