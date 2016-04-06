#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100001;
int n, a[maxn];
long long ans;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	sort(a, a + n);
	for(int i = 0, j = 0; i < n; ++i)
	{
		while(j < i && a[j] * 10 < a[i] * 9)
			++j;
		ans += i - j;
	}
	printf("%lld\n", ans);
	return 0;
}
