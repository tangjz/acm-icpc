#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 11, maxx = 21;
int n, x[maxn][3], ans;
bool vis[maxn];
void dfs(int dep, int la, int lb)
{
	if(ans < dep)
		ans = dep;
	for(int i = 1; i <= n; ++i)
		if(!vis[i])
		{
			vis[i] = 1;
			if(x[i][0] <= la && x[i][1] <= lb)
				dfs(dep + 1, x[i][0], x[i][1]);
			if(x[i][0] <= la && x[i][2] <= lb)
				dfs(dep + 1, x[i][0], x[i][2]);
			if(x[i][1] <= la && x[i][2] <= lb)
				dfs(dep + 1, x[i][1], x[i][2]);
			vis[i] = 0;
		}
}
int main()
{
	for(int Case = 1; scanf("%d", &n) == 1 && n; ++Case)
	{
		ans = 0;
		for(int i = 1; i <= n; ++i)
		{
			for(int j = 0; j < 3; ++j)
				scanf("%d", x[i] + j);
			sort(x[i], x[i] + 3);
		}
		dfs(0, maxx, maxx);
		printf("Case %d: %d\n", Case, ans);
	}
	return 0;
}
