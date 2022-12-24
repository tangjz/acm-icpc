#include <cstdio>
#include <algorithm>
using namespace std;
int n, l, a[233333];
double ans;
int main()
{
	while(scanf("%d%d", &n, &l) == 2)
	{
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		sort(a, a + n);
		ans = max(a[0], l - a[n - 1]);
		for(int i = 1; i < n; ++i)
			ans = max(ans, (a[i] - a[i - 1]) / 2.0);
		printf("%.6f\n", ans);
	}
	return 0;
}
