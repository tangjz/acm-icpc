#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 101;
int n;
struct Node
{
	int l, r;
	bool operator < (const Node &x) const
	{
		return r < x.r;
	}
} a[maxn];
int main()
{
	while(scanf("%d", &n) == 1)
	{
		for(int i = 0; i < n; ++i)
			scanf("%d%d", &a[i].l, &a[i].r);
		sort(a, a + n);
		int ans = 0, last = 0;
		for(int i = 0; i < n; ++i)
			if(a[i].l >= last)
			{
				++ans;
				last = a[i].r;
			}
		printf("%d\n", ans);
	}
	return 0;
}
