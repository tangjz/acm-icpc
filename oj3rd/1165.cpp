#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, k, a[1010];
int main()
{
	while(scanf("%d%d", &n, &k) == 2)
	{
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		sort(a, a + n);
		n = unique(a, a + n) - a;
		printf("%d\n", a[n - k]);
	}
	return 0;
}
