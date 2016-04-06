#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 50001;
int t, n, h[maxn], q, x;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d", h + i);
		sort(h, h + n);
		scanf("%d", &q);
		for(int i = 0; i < q; ++i)
		{
			scanf("%d", &x);
			printf("%d\n", lower_bound(h, h + n, x + 1) - h);
		}
	}
	return 0;
}
