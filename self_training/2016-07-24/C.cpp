#include <set>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 300001, maxm = 300001;
int n, m, kk, lnk[maxn], fa[maxn], sz[maxn], systim, tim[maxn], cnt[maxn], counter;
struct Edge
{
	int nxt, v;
} e[maxm << 1];
set<int> pt;
int find(int x)
{
	return fa[x] < 0 ? x : fa[x] = find(fa[x]);
}
bool merge(int u, int v)
{
	if((u = find(u)) == (v = find(v)))
		return 0;
	if(fa[u] > fa[v])
		swap(u, v);
	pt.erase(v);
	fa[v] = u;
	sz[u] += sz[v];
	if(fa[u] == fa[v])
		--fa[u];
	return 1;
}
int main()
{
	scanf("%d%d%d", &n, &m, &kk);
	memset(lnk + 1, -1, n * sizeof(int));
	for(int i = 0; i < m; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[i << 1] = (Edge){lnk[u], v};
		lnk[u] = i << 1;
		e[i << 1 | 1] = (Edge){lnk[v], u};
		lnk[v] = i << 1 | 1;
	}
	memset(fa + 1, -1, n * sizeof(int));
	for(int i = 2; i <= n; ++i)
	{
		pt.insert(i);
		sz[i] = 1;
	}
	for(int i = 2; i <= n; ++i)
	{
		++systim;
		for(int it = lnk[i]; it != -1; it = e[it].nxt)
		{
			if(e[it].v == 1)
			{
				++counter;
				continue;
			}
			int v = find(e[it].v);
			if(tim[v] != systim)
			{
				tim[v] = systim;
				cnt[v] = 0;
			}
			++cnt[v];
		}
		int u = find(i), v;
		for(set<int>::iterator it = pt.begin(); it != pt.end(); it = pt.lower_bound(v + 1))
		{
			v = *it;
			if(u == v)
				continue;
			if(tim[v] != systim || cnt[v] < sz[v])
			{
				merge(u, v);
				u = find(u);
			}
		}
	}
	if(kk < (int)pt.size() || kk >= n - counter)
	{
		puts("impossible");
		return 0;
	}
	++systim;
	for(int it = lnk[1]; it != -1; it = e[it].nxt)
	{
		int v = find(e[it].v);
		if(tim[v] != systim)
		{
			tim[v] = systim;
			cnt[v] = 0;
		}
		++cnt[v];
	}
	for(set<int>::iterator it = pt.begin(); it != pt.end(); ++it)
		if(tim[*it] == systim && cnt[*it] == sz[*it])
		{
			puts("impossible");
			return 0;
		}
	puts("possible");
	return 0;
}
