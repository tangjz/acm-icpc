/*
 * 行与列的二分图匹配，某行与某列连边当且仅当交叉处有一个点
 */
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;
int n, m, ans;
int match[501];
int p[501][501];
bool find(int x)
{
	for(int i = 1; i <= n; ++i)
			if(!match[i] || find(match[i]))
			{
				match[i] = x;
				return 1;
			}
	return 0;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0, u, v; i < m; ++i)
	{
		scanf("%d%d",&u, &v);
		p[u][v] = 1;
	}
	for(int i = 1; i <= n; ++i)
	{
		//if(!p[i].size()) continue;
		memset(vis, 0, sizeof vis);
		if(find(i)) ++ans;
	}
	printf("%d\n",ans);
	return 0;
}
