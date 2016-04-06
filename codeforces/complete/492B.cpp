#include <cstdio>
#include <algorithm>
using namespace std;
int n, l, a[2333];
double ans;
int main()
{
	scanf("%d%d", &n, &l);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	sort(a, a + n);
	ans = max(a[0], l - a[n - 1]);
	for(int i = 1; i < n; ++i)
		ans = max(ans, (a[i] - a[i - 1]) / 2.0);
	printf("%.10f\n", ans);
	return 0;
}
