#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1000010;
int t, n, a[maxn], l[maxn], r[maxn];
long long ans;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		l[0] = 0;
		for(int i = 1; i <= n; ++i)
			l[i] = max(l[i - 1], a[i]);
		r[n + 1] = 0;
		for(int i = n; i; --i)
			r[i] = max(r[i + 1], a[i]);
		ans = 0;
		for(int i = 1; i <= n; ++i)
			ans += min(l[i], r[i]) - a[i];
		printf("%lld\n", ans);
	}
	return 0;
}
