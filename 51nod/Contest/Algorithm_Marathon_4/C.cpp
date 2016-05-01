#pragma comment(linker, "/STACK:102400000,102400000")
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 200010, INF = 0x3f3f3f3f;
int n, m, ans;
vector<int> e[maxn];
bool vis[maxn];
int dfs(int u)
{
	int Lmax = 0, Lmin = 0;
	vis[u] = 1;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		if(vis[*it])
			continue;
		int ret = dfs(*it);
		Lmax = max(Lmax, ret);
		Lmin = min(Lmin, ret);
	}
	if(Lmin <= -m)
	{
		++ans;
		return m;
	}
	if(Lmin + Lmax > 0)
		return Lmax - 1;
	return Lmin - 1;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for(int i = 0; i < n; ++i)
    	if(!vis[i] && dfs(i) < 0)
    		++ans;
	printf("%d\n", ans);
	return 0;
}
