#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 10;
int n, l, ans;
struct Node
{
	int t, s;
	bool operator < (const Node &x) const
	{
		return t < x.t;
	}
} a[maxn];
int main()
{
	scanf("%d%d", &l, &n);
	a[0].t = 0, a[0].s = 1;
	for(int i = 1; i <= n; ++i)
		scanf("%d%d", &a[i].t, &a[i].s);
	sort(a + 1, a + n + 1);
	a[n + 1].t = l, a[n + 1].s = l + 1;
	for(int i = n; i; --i)
		if(a[i].s > a[i + 1].s + a[i + 1].t - a[i].t)
			a[i].s = a[i + 1].s + a[i + 1].t - a[i].t;
	for(int i = 1; i <= n + 1; ++i)
	{
		if(a[i].s > a[i - 1].s + a[i].t - a[i - 1].t)
			a[i].s = a[i - 1].s + a[i].t - a[i - 1].t;
		int tmp = (long long)a[i].s + a[i - 1].s + a[i].t - a[i - 1].t >> 1;
		if(ans < tmp)
			ans = tmp;
	}
	printf("%d\n", ans);
	return 0;
}
