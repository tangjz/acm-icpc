#include <cstdio>
const int maxn = 100001;
int t, n, x;
double p, f[maxn], ans;
void upd(double &x, const double &y)
{
	if(x >= y)
		x = y;
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%lf%d", &n, &p, &x);
		for(int i = 1; i <= n; ++i)
			f[i] = (f[i - 1] + 1) / (1 - p);
		ans = 2e7;
		for(int i = 1; i <= n; ++i)
		{
			int cnt = n % i;
			upd(ans, f[n / i + 1] * cnt + f[n / i] * (i - cnt) + x * i);
		}
		printf("Case #%d: %.6f\n", Case, ans);
	}
	return 0;
}
