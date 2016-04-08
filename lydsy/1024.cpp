/*
 * 每次切完的面积必然是n的整数倍 
 */
#include <cstdio>
#include <algorithm>
using namespace std;
double dfs(double x, double y, int c)
{
	if(x > y) swap(x, y);
	if(c == 1) return y / x;
	int i;
	double ans = 1e20, r = 1.0 / c;
	for(i = 1; i < c; ++i)
	{
		ans = min(ans, max(dfs(x * r * i, y, i), dfs(x - x * r * i, y, c - i)));
		ans = min(ans, max(dfs(x, y * r * i, i), dfs(x, y - y * r * i, c - i)));
	}
	return ans;
}
int main()
{
 	int n;
	double x, y;
	scanf("%lf%lf%d", &x, &y, &n);
	printf("%0.6f\n", dfs(x , y, n));
	return 0;
}
