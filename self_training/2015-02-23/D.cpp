#include <map>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
map<pair<int, int>, int> Hash;
const int maxn = 10001, maxm = 20001, maxq = 50001;
int n, m, q, p[maxn], fa[maxn], a[maxm], b[maxm], query[maxq][2], ans[maxq];
bool vis[maxm], flag;
char op[10];
int find(int x)
{
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main()
{
	while(scanf("%d", &n) != EOF)
	{
		if(flag)
			putchar('\n');
		else
			flag = 1;
		Hash.clear();
		memset(vis, 0, sizeof vis);
		for(int i = 0; i < n; ++i)
		{
			scanf("%d", p + i);
			fa[i] = i;
		}
		scanf("%d", &m);
		for(int i = 0; i < m; ++i)
		{
			scanf("%d%d", a + i, b + i);
			if(a[i] > b[i])
				swap(a[i], b[i]);
			Hash[make_pair(a[i], b[i])] = i;
		}
		scanf("%d", &q);
		for(int i = 0; i < q; ++i)
		{
			scanf("%s", op);
			if(op[0] == 'q')
			{
				query[i][0] = 0;
				scanf("%d", &query[i][1]);
			}
			else
			{
				int u, v;
				scanf("%d%d", &u, &v);
				if(u > v)
					swap(u, v);
				query[i][0] = 1;
				query[i][1] = Hash[make_pair(u, v)];
				vis[query[i][1]] = 1;
			}
		}
		for(int i = 0; i < m; ++i)
			if(!vis[i])
			{
				int u = find(a[i]), v = find(b[i]);
				if(p[u] > p[v] || p[u] == p[v] && u < v)
					swap(u, v);
				fa[u] = v;
			}
		for(int i = q - 1; i >= 0; --i)
			if(query[i][0])
			{
				if(!vis[query[i][1]])
					continue;
				int u = find(a[query[i][1]]), v = find(b[query[i][1]]);
				if(p[u] > p[v] || p[u] == p[v] && u < v)
					swap(u, v);
				fa[u] = v;
			}
			else
			{
				int u = find(query[i][1]);
				if(p[u] > p[query[i][1]])
					ans[i] = u;
				else
					ans[i] = -1;
			}
		for(int i = 0; i < q; ++i)
			if(!query[i][0])
				printf("%d\n", ans[i]);
	}
	return 0;
}
