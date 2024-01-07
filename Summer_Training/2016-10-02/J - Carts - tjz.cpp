#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100001;
int n, x[maxn], y[maxn];
LL ans[2];
int main()
{
	int px, py;
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d%d", x + i, y + i);
	sort(x, x + n);
	sort(y, y + n);
	px = x[n >> 1];
	py = y[n >> 1];
	for(int i = 0; i < n; ++i)
	{
		ans[0] += abs(x[i] - px);
		ans[1] += abs(y[i] - py);
		x[i] -= i;
		y[i] -= i;
	}
	sort(x, x + n);
	sort(y, y + n);
	px = x[n >> 1];
	py = y[n >> 1];
	for(int i = 0; i < n; ++i)
	{
		ans[1] += abs(x[i] - px);
		ans[0] += abs(y[i] - py);
	}
	printf("%lld\n", min(ans[0], ans[1]));
	return 0;
}
