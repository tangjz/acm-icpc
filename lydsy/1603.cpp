/*
 * ½¨Ê÷ºóbfs 
 */
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
typedef pair<int, int> edge;
vector<edge> g[1001];
int n, type[1001];
void dfs(const int u, const int flag)
{
	type[u] = flag;
	for(int i = 0; i < (int)g[u].size(); ++i)
		if(type[g[u][i].first] == -1)
		{
			if(g[u][i].second) dfs(g[u][i].first, flag ^ 1);
			else dfs(g[u][i].first, flag);
		}
}
int main()
{
 	int i, j, k, flag;
	scanf("%d", &n);
	for(i = 1; i < n; ++i)
	{
		scanf("%d%d%d", &j, &k, &flag);
		g[j].push_back(make_pair(k, flag));
		g[k].push_back(make_pair(j, flag));
	}
	memset(type, -1, sizeof(type));
	dfs(1, 0);
	printf("%d\n", type[n]);
	return 0;
}
