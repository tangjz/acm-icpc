#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100010;
int n, m;
vector<pair<int, int> > e[maxn];
double f[maxn];
bool vis[maxn];
void dfs(int u)
{
	vis[u] = 1;
	for(vector<pair<int, int> >::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		if(!vis[it -> first])
			dfs(it -> first);
		f[u] += f[it -> first] + it -> second;
	}
	if(e[u].size() > 0)
		f[u] /= e[u].size();
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		e[u].push_back(make_pair(v, w));
	}
	dfs(1);
	printf("%.2f\n", f[1]);
	return 0;
}
