#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1000010;
int n, a[maxn], id[maxn], fa[maxn], ans[maxn];
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
bool cmp(const int &x, const int &y)
{
	return a[x] < a[y] || a[x] == a[y] && x > y;
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		for(int i = 0; i < n; ++i)
		{
			scanf("%d", a + i);
			id[i] = i;
			fa[i] = i;
		}
		sort(id, id + n, cmp);
		fa[n] = n;
		a[n] = -1;
		for(int i = 0; i < n; ++i)
			ans[id[i]] = fa[id[i]] = find(id[i] + 1);
		for(int i = 0; i < n; ++i)
			printf("%d\n", a[ans[i]]);
	}
	return 0;
}
