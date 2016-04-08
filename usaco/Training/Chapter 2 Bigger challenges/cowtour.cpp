/*
ID: tangjin2
LANG: C++
TASK: cowtour
*/
#include <cmath>
#include <cstdio>
const int maxn = 151;
const double INF = 1e10;
int n, x[maxn], y[maxn];
double f[maxn][maxn], g[maxn], h[maxn], ans;
char str[maxn];
void upd(double &x, double y)
{
	if(x < y)
		x = y;
}
int main()
{
	freopen("cowtour.in", "r", stdin);
	freopen("cowtour.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d%d", x + i, y + i);
	for(int i = 0; i < n; ++i)
	{
		scanf("%s", str);
		for(int j = 0; j < n; ++j)
			if(i == j || str[j] == '1')
				f[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
			else
				f[i][j] = INF;
	}
	for(int k = 0; k < n; ++k)
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				if(f[i][j] > f[i][k] + f[k][j])
					f[i][j] = f[i][k] + f[k][j];
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			if(f[i][j] < INF * 0.5)
				upd(g[i], f[i][j]);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			if(f[i][j] < INF * 0.5)
				upd(h[i], g[j]);
	ans = INF;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
		{
			if(f[i][j] < INF * 0.5)
				continue;
			double tmp = g[i] + g[j] + sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
			upd(tmp, h[i]);
			upd(tmp, h[j]);
			if(ans > tmp)
				ans = tmp;
		}
	printf("%.6f\n", ans);
	return 0;
}
