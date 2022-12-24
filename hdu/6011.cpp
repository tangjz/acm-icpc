#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 27;
int t, n;
pair<int, int> a[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d%d", &a[i].first, &a[i].second);
		sort(a, a + n);
		LL ans = 0, dt = 0;
		for(int i = n - 1; i >= 0; --i)
			for(int j = 0; j < a[i].second; ++j)
			{
				dt += a[i].first;
				if(dt >= 0)
					ans += dt;
			}
		printf("%I64d\n", ans);
	}
	return 0;
}
