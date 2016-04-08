#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 10001;
int n, a[maxn];
long long sum, ans;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	sort(a, a + n);
	for(int i = 0; i < n; ++i)
	{
		ans += (long long)i * a[i] - sum;
		sum += a[i];
	}
	printf("%lld\n", ans * 2);
	return 0;
}
