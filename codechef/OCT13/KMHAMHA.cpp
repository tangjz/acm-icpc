#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
vector<int> g[1001];
int n, match[1001];
bool vis[1001];
bool dfs(int u)
{
	for(vector<int>::iterator it = g[u].begin(); it != g[u].end(); ++it)
		if(!vis[*it])
		{
			vis[*it] = 1;
			if(match[*it] == -1 || dfs(match[*it]))
			{
				match[*it] = u;
				return 1;
			}
		}
	return 0;
}
struct Point { int num, id; } x[1001], y[1001];
int point[1001][2];
bool cmp(const Point &a, const Point &b) { return a.num < b.num; }
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		int i, u, v, r = 0, c = 0, ans = 0;
		scanf("%d",&n);
		for(i = 0; i < n; ++i)
		{
			scanf("%d%d", &u, &v);
			x[i] = (Point){u, i};
			y[i] = (Point){v, i};
		}
		sort(x, x + n, cmp);
		sort(y, y + n, cmp);
		for(i = 0; i < n; ++i)
		{
			point[x[i].id][0] = r, point[y[i].id][1] = c;
			if(x[i].num != x[i + 1].num) ++r;
			if(y[i].num != y[i + 1].num) ++c;
		}
		for(int i = 0; i <= r; ++i) g[i].clear();
		for(i = 0; i < n; ++i) g[point[i][0]].push_back(point[i][1]);
		memset(match, -1, sizeof match);
		for(int i = 0; i <= r; ++i)
		{
			memset(vis, 0, sizeof vis);
			if(dfs(i)) ++ans;
		}
		printf("%d\n", ans);
	}
	return 0;
}
