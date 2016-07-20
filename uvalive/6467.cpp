#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1010;
int t, id, n, m, f[maxn], ans;
vector<int> e[maxn];
void dfs(int u)
{
	int mx1 = 0, mx2 = 0;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		if(!f[*it])
			dfs(*it);
		if(mx1 <= f[*it])
		{
			mx2 = mx1;
			mx1 = f[*it];
		}
		else if(mx2 <= f[*it])
			mx2 = f[*it];
	}
	f[u] = mx1 + (mx1 == mx2);
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		ans = 0;
		memset(f, 0, sizeof f);
		scanf("%d%d%d", &id, &n, &m);
		for(int i = 1; i <= n; ++i)
			e[i].clear();
		for(int i = 1; i <= m; ++i)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			e[v].push_back(u);
		}
		for(int i = 1; i <= n; ++i)
			if(!f[i])
			{
				dfs(i);
				if(ans < f[i])
					ans = f[i];
			}
		printf("%d %d\n", id, ans);
	}
	return 0;
}
