#include <cmath>
#include <cstdio>
const int maxn = 31, maxm = 31, INF = 3000;
const double eps = 1e-12, pi = 3.1415926535897;
int n, m[maxn], x[maxn][maxm], y[maxn][maxm], r[maxn][maxm], pos;
double area[maxn], ans[maxn][2];
bool vis[maxn];
int dcmp(double x)
{
	if(fabs(x) < eps)
		return 0;
	return x > 0 ? 1 : -1;
}
bool check(double xmax, int frac)
{
	for(int i = 0; i < n; ++i)
	{
		if(vis[i])
			continue;
		double ret = 0;
		for(int j = 0; j < m[i]; ++j)
		{
			if(dcmp(x[i][j] - r[i][j] - xmax) >= 0)
				continue;
			if(dcmp(x[i][j] + r[i][j] - xmax) <= 0)
				ret += pi * r[i][j] * r[i][j];
			else
			{
				double theta = 2 * acos(fabs(xmax - x[i][j]) / r[i][j]);
				if(dcmp(x[i][j] - xmax) < 0)
					ret += r[i][j] * r[i][j] * (pi - (theta - sin(theta)) / 2);
				else
					ret += r[i][j] * r[i][j] * (theta - sin(theta)) / 2;
			}
		}
		if(dcmp(ret * n - area[i] * frac) >= 0)
		{
			pos = i;
			return 1;
		}
	}
	return 0;
}
int main()
{
	double L = INF, R = -INF, M;
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", m + i);
		for(int j = 0; j < m[i]; ++j)
		{
			scanf("%d%d%d", x[i] + j, y[i] + j, r[i] + j);
			area[i] += pi * r[i][j] * r[i][j];
			if(L > x[i][j] - r[i][j])
				L = x[i][j] - r[i][j];
			if(R < x[i][j] + r[i][j])
				R = x[i][j] + r[i][j];
		}
	}
	R += 1;
	for(int i = 0; i < n; ++i)
	{
		double tmp1 = L, tmp2 = R;
		for(int j = 0; j < 100; ++j)
		{
			M = (L + R) / 2;
			if(check(M, i + 1))
				R = M;
			else
				L = M;
		}
		vis[pos] = 1;
		ans[pos][0] = tmp1;
		ans[pos][1] = R;
		L = R;
		R = tmp2;
	}
	for(int i = 0; i < n; ++i)
		printf("4\n%.8f %d\n%.8f %d\n%.8f %d\n%.8f %d\n", ans[i][0], INF, ans[i][0], -INF, ans[i][1], -INF, ans[i][1], INF);
	return 0;
}
