#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2001;
int t, n, m, a[maxn], ans;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		ans = 0;
		scanf("%d%d", &n, &m);
		for(int i = 0, x; i < n + m; ++i)
			scanf("%d", a + i);
		sort(a, a + n + m);
		for(int i = 0; i < n; ++i)
			ans += a[i];
		printf("%d\n", ans);
	}
	return 0;
}
