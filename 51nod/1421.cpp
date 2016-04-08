#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 200010, maxs = 1000010;
int n, a[maxn], f[maxs], ans;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	sort(a, a + n);
	n = unique(a, a + n) - a;
	for(int i = 0; i < n; ++i)
		for(int j = a[i] + 1; j <= a[i + 1]; ++j)
			f[j] = a[i];
	for(int i = 0; i < n; ++i)
	{
		for(int j = a[i] * 2; j <= a[n - 1]; j += a[i])
			ans = max(ans, f[j] % a[i]);
		ans = max(ans, a[n - 1] % a[i]);
	}
	printf("%d\n", ans);
	return 0;
}
