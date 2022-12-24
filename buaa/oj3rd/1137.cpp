#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 100010;
int n, m, t[maxn], f[maxn], ans;
vector<int> e[maxn];
int max(int a, int b)
{
	return a < b ? b : a;
}
int F(int v)
{
	if(f[v] != -1)
		return f[v];
	int Max = 0;
	for(int i = 0, j = (int)e[v].size(); i < j; ++i)
		Max = max(Max, F(e[v][i]));
	return f[v] = Max + t[v];
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		ans = 0;
		memset(f, -1, sizeof f);
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", t + i);
			e[i].clear();
		}
		for(int u, v; m--; )
		{
			scanf("%d%d", &u, &v);
			e[v].push_back(u);
		}
		for(int i = 1; i <= n; ++i)
			ans = max(ans, F(i));
		printf("%d\n", ans);
	}
	return 0;
}
