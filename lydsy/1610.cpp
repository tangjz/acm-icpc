#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 233;
int n, x[maxn], y[maxn], tot;
pair<int, int> p[maxn * maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d%d", x + i, y + i);
	for(int i = 1; i <= n; ++i)
		for(int j = i + 1; j <= n; ++j)
		{
			int dx = x[i] - x[j], dy = y[i] - y[j];
			if(dx < 0)
			{
				dx = -dx;
				dy = -dy;
			}
			if(!dx)
				dy = 1;
			else if(!dy)
				dx = 1;
			else
			{
				int r = __gcd(dx, abs(dy));
				dx /= r;
				dy /= r;
			}
			p[tot++] = {dx, dy};
		}
	sort(p, p + tot);
	tot = unique(p, p + tot) - p;
	printf("%d\n", tot);
	return 0;
}
