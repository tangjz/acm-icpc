#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1010;
int n, x[maxn], y[maxn], ansx, ansy, ans;
int main()
{
	for(int Case = 1; scanf("%d", &n) == 1 && n; ++Case)
	{
		for(int i = 0; i < n; ++i)
			scanf("%d%d", x + i, y + i);
		sort(x, x + n);
		sort(y, y + n);
		ansx = x[n - 1 >> 1];
		ansy = y[n - 1 >> 1];
		ans = 0;
		for(int i = 0; i < n; ++i)
			ans += abs(x[i] - ansx) + abs(y[i] - ansy);
		printf("Case %d: (%d,%d) %d\n", Case, ansx, ansy, ans);
	}
	return 0;
}
