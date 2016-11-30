#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 10001, maxd = 10001;
int n, fa[maxd], ans;
struct Node
{
	int p, d;
	bool operator < (const Node &x) const
	{
		return p > x.p;
	}
} a[maxn];
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	while(scanf("%d", &n) != EOF)
	{
		for(int i = 0; i < maxd; ++i)
			fa[i] = i;
		for(int i = 0; i < n; ++i)
			scanf("%d%d", &a[i].p, &a[i].d);
		sort(a, a + n);
		ans = 0;
		for(int i = 0; i < n; ++i)
		{
			int x = find(a[i].d);
			if(x)
			{
				fa[x] = find(x - 1);
				ans += a[i].p;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
