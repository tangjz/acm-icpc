#include <cstdio>
const int maxn = 100010, maxm = 66;
const double INF = 1e10;
int n, s[maxn], x[maxn], p[maxn];
double f[maxn];
inline void upd(double &x, double y)
{
	if(x > y)
		x = y;
}
int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d%d%d", s + i, x + i, p + i);
		f[i] = INF;
	}
	for(int i = 0; i < n; ++i)
	{
		double delta = 0;
		for(int j = 1; j < maxm && i + j <= n; ++j)
		{
			delta += s[i + j];
			upd(f[i + j], f[i] + delta + x[i + j]);
			delta *= (100 + p[i + j]) / 100.0;
		}
	}
	printf("%.10f\n", f[n]);
	return 0;
}
