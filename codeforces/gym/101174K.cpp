#include <set>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef pair<pair<int, int>, int> triple;
const int maxn = 100001;
int n, tot, dsu[maxn];
triple a[maxn], que[maxn];
int dsu_find(int x)
{
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
set<pair<int, int> > multi;
bool dsu_merge(int u, int v)
{
	if(u == v)
		return 1;
	if(u > v)
		swap(u, v);
	if(multi.count(make_pair(u, v)))
		return 1;
	multi.insert(make_pair(u, v));
	u = dsu_find(u);
	v = dsu_find(v);
	if(u == v)
		return 0;
	if(dsu[u] > dsu[v])
		swap(u, v);
	if(dsu[u] == dsu[v])
		--dsu[u];
	dsu[v] = u;
	return 1;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d%d%d", &a[i << 1].first.first, &a[i << 1].first.second, &a[i << 1].second);
		scanf("%d%d%d", &a[i << 1 | 1].first.first, &a[i << 1 | 1].first.second, &a[i << 1 | 1].second);
		que[i << 1] = a[i << 1];
		que[i << 1 | 1] = a[i << 1 | 1];
	}
	sort(que, que + (n << 1));
	tot = unique(que, que + (n << 1)) - que;
	memset(dsu, -1, tot * sizeof(int));
	bool flag = 1;
	multi.clear();
	for(int i = 0; i < n && flag; ++i)
		flag &= dsu_merge(lower_bound(que, que + tot, a[i << 1]) - que, lower_bound(que, que + tot, a[i << 1 | 1]) - que);
	puts(!flag ? "True closed chains" : "No true closed chains");
	for(int i = 0; i < tot; ++i)
		que[i].second = 0;
	tot = unique(que, que + tot) - que;
	memset(dsu, -1, tot * sizeof(int));
	flag = 1;
	multi.clear();
	for(int i = 0; i < n && flag; ++i)
	{
		a[i << 1].second = a[i << 1 | 1].second = 0;
		flag &= dsu_merge(lower_bound(que, que + tot, a[i << 1]) - que, lower_bound(que, que + tot, a[i << 1 | 1]) - que);
	}
	puts(!flag ? "Floor closed chains" : "No floor closed chains");
	return 0;
}
