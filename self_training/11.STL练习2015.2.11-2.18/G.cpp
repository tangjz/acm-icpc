#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 1;
int t, n, ans;
struct Node
{
	int h, w;
	bool operator < (const Node &x) const
	{
		return h < x.h;
	}
} a[maxn], b[maxn];
multiset<int> y;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		y.clear();
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d%d", &a[i].h, &a[i].w);
		sort(a, a + n);
		for(int i = 0; i < n; ++i)
			scanf("%d%d", &b[i].h, &b[i].w);
		sort(b, b + n);
		ans = 0;
		for(int i = 0, j = 0; i < n; ++i)
		{
			while(j < n && b[j].h <= a[i].h)
				y.insert(b[j++].w);
			if(y.empty())
				continue;
			multiset<int>::iterator it = y.upper_bound(a[i].w);
			if(it != y.begin())
			{
				y.erase(--it);
				++ans;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
