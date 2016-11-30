#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = (int)6e4;
int t, n, g[maxn], ans;
struct Node
{
	int l, w;
	bool operator < (const Node &x) const
	{
		return l < x.l || l == x.l && w < x.w;
	}
} a[maxn];
int BinarySearch(int l, int r, int val)
{
	while(l < r)
	{
		int m = l + r >> 1;
		if(g[m] <= val)
			r = m;
		else
			l = m + 1;
	}
	return l;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		ans = 0;
		memset(g, 0, sizeof g);
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			scanf("%d%d", &a[i].l, &a[i].w);
		sort(a + 1, a + n + 1);
		for(int i = 1; i <= n; ++i)
		{
			int k = BinarySearch(1, n, a[i].w);
			g[k] = max(g[k], a[i].w);
			ans = max(ans, k);
		}
		printf("%d\n", ans);
	}
	return 0;
}
