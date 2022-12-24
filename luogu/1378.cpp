#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const double pi = acos(-1);
int n;
bool used[6];
double a0, b0, a1, b1, x[6], y[6], r[6], ans;
void dfs(int dep)
{
	if(dep == n)
	{
		double sum = 0.0;
		for(int i = 0; i < n; ++i) sum += pi * r[i] * r[i];
		ans = max(ans, sum);
		return;
	}
	for(int i = 0; i < n; ++i) if(!used[i])
	{
		used[i] = 1;
		r[i] = 10000.0;
		for(int j = 0; j < n; ++j) if(i != j && used[j])
			r[i] = min(r[i], max(0.0, sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j])) - r[j]));
		r[i] = min(r[i], min(min(fabs(x[i] - a0), fabs(x[i] - a1)), min(fabs(y[i] - b0), fabs(y[i] - b1))));
		dfs(dep + 1);
		used[i] = 0;
		r[i] = 0.0;
	}
}
int main()
{
	scanf("%d%lf%lf%lf%lf", &n, &a0, &b0, &a1, &b1);
	for(int i = 0; i < n; ++i) scanf("%lf%lf", &x[i], &y[i]);
	dfs(0);
	printf("%.0lf\n", fabs(a0 - a1) * fabs(b0 - b1) - ans);
	return 0;
}