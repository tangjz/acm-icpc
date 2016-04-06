#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 5e4;
int n, ans;
struct Node
{
	int s, e;
	bool operator < (const Node &x) const
	{
		return e < x.e;
	}
} a[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d%d", &a[i].s, &a[i].e);
	sort(a, a + n);
	for(int i = 0, last = a[0].s; i < n; ++i)
		if(a[i].s >= last)
		{
			++ans;
			last = a[i].e;
		}
	printf("%d\n", ans);
	return 0;
}
