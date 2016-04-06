#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 50001;
const double eps = 1e-8;
int n, x[maxn], r[maxn];
pair<double, int> point[maxn << 1];
int dcmp(double x)
{
	if(fabs(x) < eps)
		return 0;
	return x < 0 ? -1 : 1;
}
bool check(double lim)
{
	int cnt = 0;
	for(int i = 0; i < n; ++i)
	{
		if(dcmp(r[i] - lim) <= 0)
			continue;
		double delta = sqrt((double)r[i] * r[i] - lim * lim);
		point[cnt++] = make_pair(x[i] - delta, -1);
		point[cnt++] = make_pair(x[i] + delta, 1);
	}
	sort(point, point + cnt);
	double sta;
	for(int i = 0, j = 0; i < cnt; ++i)
	{
		if(!j)
			sta = point[i].first;
		j += point[i].second;
		if(!j && dcmp(point[i].first - sta - 2 * lim) >= 0)
			return 1;
	}
	return 0;
}
int main()
{
	while(scanf("%d", &n) == 1 && n)
	{
		for(int i = 0; i < n; ++i)
			scanf("%d%d", x + i, r + i);
		double L = 0, R = 1e5;
		for(int i = 0; i < 50; ++i)
		{
			double M = L + (R - L) / 2;
			if(check(M))
				L = M;
			else
				R = M;
		}
		printf("%.8f\n", L * 2);
	}
	return 0;
}
