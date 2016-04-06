#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1001;
int n, a[maxn], pos, ans;
int main()
{
	while(scanf("%d", &n) != EOF)
	{
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		sort(a, a + n);
		for(int i = 0; i < n; ++i)
			a[i] -= i;
		pos = a[n >> 1];
		ans = 0;
		for(int i = 0; i < n; ++i)
			ans += a[i] <= pos ? pos - a[i] : a[i] - pos;
		printf("%d\n", ans);
	}
	return 0;
}
