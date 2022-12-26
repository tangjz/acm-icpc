/*
 * 1693
 */
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, ans;
int match[501];
bool vis[501];
vector<int> p[501];
bool find(int x)
{
	for(vector<int>::iterator it = p[x].begin(); it != p[x].end(); ++it)
		if(!vis[*it])
		{
			vis[*it] = 1;
			if(!match[*it] || find(match[*it]))
			{
				match[*it] = x;
				return 1;
			}
		}
	return 0;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0, u, v; i < m; ++i)
	{
		scanf("%d%d",&u, &v);
		p[u].push_back(v);
	}
	for(int i = 1; i <= n; ++i)
	{
		if(!p[i].size()) continue;
		memset(vis, 0, sizeof vis);
		if(find(i)) ++ans;
	}
	printf("%d\n",ans);
	return 0;
}
