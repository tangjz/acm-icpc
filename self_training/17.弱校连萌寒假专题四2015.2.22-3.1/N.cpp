#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100001;
int n, f[maxn], g[maxn], pre[maxn], out[maxn], ans;
struct Node
{
	int id, s, b;
	bool operator < (const Node &x) const
	{
		return b < x.b;
	}
} a[maxn];
bool cmp(const Node &x, const Node &y)
{
	return x.s < y.s || x.s == y.s && x.b > y.b;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		a[i].id = i;
		scanf("%d%d", &a[i].s, &a[i].b);
	}
	sort(a + 1, a + n + 1, cmp);
	for(int i = 1; i <= n; ++i)
	{
		int k = upper_bound(f + 1, f + ans + 1, a[i].b - 1) - f;
		pre[i] = g[k - 1];
		f[k] = a[i].b;
		g[k] = i;
		if(ans < k)
			ans = k;
	}
	printf("%d\n", ans);
	for(int i = ans - 1, j = g[ans]; i >= 0; --i, j = pre[j])
		out[i] = a[j].id;
	for(int i = 0; i < ans; ++i)
		printf("%d%c", out[i], " \n"[i == ans - 1]);
	return 0;
}
