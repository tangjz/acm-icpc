#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100001;
int t, n, m, a[maxn], p[maxn], bit[maxn], l[maxn], r[maxn], id[maxn], ans[maxn];
void add(int x, int v)
{
	for( ; x <= n; x += x & -x)
		bit[x] += v;
}
int sum(int x)
{
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
bool cmp(const int &x, const int &y)
{
	return r[x] < r[y];
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", a + i);
			p[a[i]] = i;
		}
		for(int i = 0; i < m; ++i)
		{
			scanf("%d%d", l + i, r + i);
			id[i] = i;
		}
		sort(id, id + m, cmp);
		memset(bit, 0, sizeof bit);
		for(int i = 1, j = 0; i <= n; ++i)
		{
			add(i, 1);
			if(a[i] > 1 && p[a[i] - 1] <= i)
				add(p[a[i] - 1], -1);
			if(a[i] < n && p[a[i] + 1] <= i)
				add(p[a[i] + 1], -1);
			for( ; r[id[j]] == i; ++j)
				ans[id[j]] = sum(r[id[j]]) - sum(l[id[j]] - 1);
		}
		for(int i = 0; i < m; ++i)
			printf("%d\n", ans[i]);
	}
	return 0;
}
