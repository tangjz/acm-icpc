#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 101;
int t, n, k, a[maxn], ans;
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d", &n, &k);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		sort(a, a + n);
		ans = 1;
		for(int i = 1; i < n; ++i)
			if(a[i] - a[i - 1] > k)
				++ans;
		printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}
