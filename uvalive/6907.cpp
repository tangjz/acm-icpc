#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 101, maxm = 4951;
int t, n, m, deg[maxn], fa[maxn], bri[maxn][3], tmp_s, tmp_c, tmp_t, ans;
vector<int> e[maxn];
bool vis[maxn];
int find(int x)
{
	return fa[x] < 0 ? x : fa[x] = find(fa[x]);
}
void dfs(int u)
{
	vis[u] = 1;
	++tmp_c;
	if(deg[u] == tmp_s - 1)
		++tmp_t;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		if(!vis[*it])
			dfs(*it);
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		ans = 0;
		memset(deg, 0, sizeof deg);
		memset(fa, -1, sizeof fa);
		memset(bri, 0, sizeof bri);
		memset(vis, 0, sizeof vis);
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i)
			e[i].clear();
		for(int i = 0, u, v; i < m; ++i)
		{
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			e[v].push_back(u);
			++deg[u];
			++deg[v];
			if((u = find(u)) != (v = find(v)))
			{
				fa[u] += fa[v];
				fa[v] = u;
			}
		}
		for(int i = 1; i <= n; ++i)
		{
			if(fa[find(i)] & 1)
				continue;
			if(deg[i] == -fa[find(i)] / 2)
			{
				++bri[find(i)][0];
				if(bri[find(i)][0] <= 2)
					bri[find(i)][bri[find(i)][0]] = i;
			}
		}
		for(int i = 1; i <= n; ++i)
		{
			if(i != find(i) || bri[i][0] != 2)
				continue;
			vis[bri[i][2]] = 1;
			tmp_s = -fa[i] / 2;
			tmp_c = 0;
			tmp_t = 1;
			dfs(bri[i][1]);
			if(tmp_s != tmp_c || tmp_c != tmp_t)
				continue;
			vis[bri[i][2]] = 0;
			tmp_c = 0;
			tmp_t = 1;
			dfs(bri[i][2]);
			if(tmp_s == tmp_t && tmp_c == tmp_t)
				++ans;
		}
		printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}
