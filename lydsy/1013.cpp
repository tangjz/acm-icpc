/*
 * ∑x[i] * 2 * (b[i] - a[i]) = ∑b[i]^2 - a[i]^2
 */
#include <cstdio>
#include <algorithm>
using namespace std;
int n;
double a[13][13] = {}, b[13][13] = {}, x[13] = {}, m;
int main()
{
	int i, j, k;
	scanf("%d", &n);
	for(i = 1; i <= n + 1; ++i)
		for(j = 1; j <= n; ++j) scanf("%lf", &b[i][j]);
	for(i = 1; i <= n; ++i)
		for(j = 1; j <= n; ++j)
		{
			a[i][j] = (b[i + 1][j] - b[i][j]) * 2;
			a[i][n + 1] += b[i + 1][j] * b[i + 1][j] - b[i][j] * b[i][j];
		}
	for(i = 1; i < n; ++i)
	{
		k = i;
		for(j = i + 1; j <= n; ++j)
			if(a[j][i] > a[k][i]) k = j;
		for(j = i; j <= n + 1; ++j) swap(a[i][j], a[k][j]);
		for(j = i + 1; j <= n; ++j)
		{
			m = a[j][i] / a[i][i];
			for(k = i; k <= n + 1; ++k) a[j][k] = a[i][k] * m - a[j][k];
		}
	}
	x[n] = a[n][n + 1] / a[n][n];
	for(i = n - 1; i >= 1; --i)
	{
		m = 0;
		for(j = i + 1; j <= n; ++j) m += a[i][j] * x[j];
		x[i] = (a[i][n + 1] - m) / a[i][i];
	}
	for(i = 1; i <= n - 1; ++i) printf("%.3lf ", x[i]);
	printf("%.3lf\n", x[i]);
	return 0;
}
