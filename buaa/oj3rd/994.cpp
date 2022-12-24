#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100001;
int n, x[maxn];
long long ans;
int main()
{
	while(scanf("%d", &n) != EOF)
	{
		ans = 0;
		for(int i = 0; i < n; ++i)
			scanf("%d", x + i);
		sort(x, x + n);
		for(int i = 0; i < n; ++i)
			ans += x[i] < x[n >> 1] ? x[n >> 1] - x[i] : x[i] - x[n >> 1];
		printf("%lld\n", ans << 1);
	}
	return 0;
}
