#include <cstdio>
#include <algorithm>
using namespace std;
const int INF = ~0u >> 1;
int n, x0 = INF, x1, x2, x3, y0 = INF, y1, y2, y3, sum;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		x0 = min(x0, x1);
		x3 = max(x3, x2);
		y0 = min(y0, y1);
		y3 = max(y3, y2);
		sum += (x2 - x1) * (y2 - y1);
	}
	if(x3 - x0 == y3 - y0 && sum == (x3 - x0) * (y3 - y0)) puts("YES");
	else puts("NO");
	return 0;
}
