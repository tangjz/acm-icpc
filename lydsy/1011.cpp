/*
 * 先推出O(N^2)的万有引力计算公式 然后近似计算 = =
 */
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const int T = 100;
const double eps = 1e-8;
int M[100100], n;
double a, F[100100] = {};
int main()
{
	int l, r, i, j;
	scanf("%d%lf", &n, &a);
	for(i = 1; i <= n; ++i) scanf("%d", &M[i]);
	for(i = 1; i <= T; ++i)
	{
		r = (int)(eps + floor(a * i));
		for(j = 1; j <= r; ++j) F[i] += 1.0 * M[i] * M[j] / (i - j);
	}
	for(i = T + 1; i <= n; ++i)
	{
		l = (int)(eps + floor(a * (i - T)));
		r = (int)(eps + floor(a * i));
		for(j = l + 1; j <= r; ++j) F[i] += 1.0 * M[i] * M[j] /(i - j);
		F[i] += 1.0 * M[i] * (F[i - T]/ M[i - T]) * (i - T - 1.0 * l / 2) / (i - 1.0 * l / 2);
	}
	for(i = 1; i <= n; ++i) printf("%.6lf\n", F[i]);
	return 0;
}
